#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include "Features/Features.h"
#include "program/program.h"
#include "functions/function_store/function_store.h"
#include "thread_pool/thread_pool.h"


using namespace std;

enum generation_method
{
    Grow,
    Full,
    Ramped_Half_And_Half
};

enum data_set_type
{
    Valid = 0,
    Train = 1,
    Test = 2
};

struct parameters
{
    vector<unsigned int> seeds;
    unsigned int runs;
    unsigned int generations;
    unsigned int max_depth;
    unsigned int population_size;
    unsigned int tournament_size;
    unsigned int mutation_depth;
    unsigned int offspring_depth;
    double crossover_rate;
    double mutation_rate;
    generation_method generation_method;
    double bound;
};

#define max_size 9601139
#define valid_size 2000000
#define train_size 3800570
#define test_size 3800569

vector<program> population;
Features* data_set = nullptr;
unsigned int data_size = 0; //1679489208
parameters params = {
    {1579688843, 1679681008, 1079688975, 99689032, 7516890, 690833, 5715796, 3679689135, 1119689183, 1129489208},   //seeds
    10,  //runs
    50,  //generations
    3,  //max_depth
    200,    //population_size
    4,  //tournament_size
    3,  //mutation_depth
    18, //offspring_depth
    0.65,    //crossover_rate
    0.35,    //mutation_rate
    Ramped_Half_And_Half   //generation_method
};
mutex mutex_object;

void load_and_split_and_save();
Features extract(string sline);
void load(data_set_type dtype = Valid);
void initial_population();
unsigned int select_program();
pair<program,program> crossover(program& parent_one,program& parent_two);
program mutate(program& parent);
program genetic_program();
void threaded_genetic_program();

int main()
{
    load(Train);
    program model = genetic_program();

    load(Test);
    model.set_fitness(data_set, data_size);
    model.set_root_mean_square_error(data_set, data_size);   
    model.set_mean_absolute_error(data_set, data_size);
    model.set_median_absolute_error(data_set, data_size);
    model.set_r_squared(data_set, data_size);

    cout<<endl;
    cout<<"fitness: "<<to_string(model.get_fitness())<<endl;
    cout<<"root mean square error: "<<to_string(model.get_root_mean_square_error())<<endl;
    cout<<"r squared: "<<to_string(model.get_r_squared())<<endl;
    cout<<"mean absolute error: "<<to_string(model.get_mean_absolute_error())<<endl;
    cout<<"median absolute error: "<<to_string(model.get_median_absolute_error())<<endl;
    cout<<endl;

    delete data_set;

    return 0;
}

void load_and_split_and_save()
{
    delete data_set;
    data_set = new Features[max_size];

    fstream file("dataset/text_data/data.csv", ios::in);

    fstream valid_file("dataset/text_data/valid.csv", ios::out);
    fstream train_file("dataset/text_data/train.csv", ios::out);
    fstream test_file("dataset/text_data/test.csv", ios::out);
    
    fstream valid_binary_file("dataset/binary_data/valid.dat", ios::binary | ios::out);
    fstream train_binary_file("dataset/binary_data/train.dat", ios::binary | ios::out);
    fstream test_binary_file("dataset/binary_data/test.dat", ios::binary | ios::out);

    unsigned int valid_max = valid_size;
    unsigned int train_max = valid_size + train_size;
    
    string sline;
    int counter = 0;

    getline(file, sline, '\n');

    while(!file.eof())
    {
        if(sline == "")
        {
            continue;
        }

        getline(file, sline, '\n');
        Features entry = extract(sline);

        if(entry.duration == 0)
        {
            continue;
        }

        data_set[counter] = entry;

        if(counter < valid_max)
        {
            data_set[counter].save_text(valid_file, counter);
            valid_binary_file.write((char*)(data_set + counter),sizeof(Features));
        }else if(counter < train_max)
        {
            data_set[counter].save_text(train_file, counter);
            train_binary_file.write((char*)(data_set + counter), sizeof(Features));
        }else
        {
            data_set[counter].save_text(test_file, counter);
            test_binary_file.write((char*)(data_set + counter), sizeof(Features));
        }

        counter++;
    }

    data_size = counter;
    
    file.close();
    valid_file.close();
    train_file.close();
    test_file.close();

    valid_binary_file.close();
    train_binary_file.close();
    test_binary_file.close();
}

void load(data_set_type dtype)
{
    delete data_set;
    
    fstream file;

    switch (dtype)
    {
        case Valid:{
            file.open("dataset/binary_data/valid.dat", ios::binary | ios::in );
            data_size = valid_size;
            data_set = new Features[data_size];
        }break;
        case Train:{
            file.open("dataset/binary_data/train.dat",ios::binary | ios::in);
            data_size = train_size;
            data_set = new Features[data_size];
        }break;
        case Test:{
            file.open("dataset/binary_data/test.dat",ios::binary | ios::in );
            data_size = test_size;
            data_set = new Features[data_size];
        }break;
    }


    if(file.fail())
    {
        throw string("Error: failed to open the file");
    }else
    {
        int counter = 0;

        while(!file.eof() && counter < data_size)
        {
            file.read((char*)(data_set + counter),sizeof(Features));
            counter++;
        }

        file.close();
    }
}

void initial_population()
{
    population.clear();

    switch(params.generation_method)
    {
        case Grow:
        {
            for(int count = 0; count < params.population_size; count++)
            {
                program individual;
                individual.build(params.max_depth, true);

                population.push_back(move(individual));
            }
        }break;
        case Full:
        {
            for(int count = 0; count < params.population_size; count++)
            {
                program individual;
                individual.build(params.max_depth, false);

                population.push_back(move(individual));
            }
        }break;
        case Ramped_Half_And_Half:
        {
            unsigned int depth = 2;

            while(population.size() < params.population_size)
            {
                program grow_individual;
                
                grow_individual.build(depth,true);
                population.push_back(move(grow_individual));

                if(population.size() < params.population_size)
                {
                    program full_individual;

                    full_individual.build(depth,false);
                    population.push_back(move(full_individual));
                }

                depth = (depth + 1) % (params.max_depth + 1);
                depth = depth < 2 ? 2 : depth;
            }
        }break;
    }
}

unsigned int select_program()
{
    int random_index = rand() % population.size();
    int result_index = random_index;

    for(int count = 1; count < params.tournament_size; count++)
    {
        random_index = rand() % population.size();
        if(population[random_index].get_fitness() < population[result_index].get_fitness())
        {
            result_index = random_index;
        }
    }

    return result_index;
}

pair<program,program> crossover(program& parent_one,program& parent_two)
{
    program offspring_one(parent_one);
    program offspring_two(parent_two);

    int crossover_index_one = rand() % parent_one.count_nodes();
    int crossover_index_two = rand() % parent_two.count_nodes();

    pair<shared_ptr<primitive>, shared_ptr<primitive>> crossover_point_one = offspring_one.get_node(crossover_index_one);
    pair<shared_ptr<primitive>, shared_ptr<primitive>> crossover_point_two = offspring_two.get_node(crossover_index_two);


    if(crossover_point_one.first.use_count() == 0)
    {
        offspring_one.set_root(crossover_point_two.second->clone());
    }else
    {
        for(int count = 0; count < crossover_point_one.first->arguments_size(); count++)
        {
            if(crossover_point_one.first->get(count) == crossover_point_one.second)
            {
                crossover_point_one.first->set(count,crossover_point_two.second->clone()); 
                break;
            } 
        }
    }

    if(crossover_point_two.first.use_count() == 0)
    {
        offspring_two.set_root(crossover_point_one.second->clone());
    }else
    {
        for(int count = 0; count < crossover_point_two.first->arguments_size(); count++)
        {
            if(crossover_point_two.first->get(count) == crossover_point_two.second)
            {
                crossover_point_two.first->set(count,crossover_point_one.second->clone());
                break;
            }
        }
    }

    return make_pair(offspring_one,offspring_two);
}

program mutate(program& parent)
{
    program result(parent);
    program segment;

    unsigned int mutation_index = rand() % parent.count_nodes();

    pair<shared_ptr<primitive>, shared_ptr<primitive>> mutation_point = result.get_node(mutation_index);

    segment.build(params.mutation_depth,false);

    if(mutation_point.first.use_count() == 0)
    {
        result.set_root(segment.get_root());    
    }else
    {
        for(int count = 0; count < mutation_point.first->arguments_size(); count++)
        {
            if(mutation_point.first->get(count) == mutation_point.second)
            {
                mutation_point.first->set(count, segment.get_root());
                break;
            }
        }
    }

    return result;
}

program genetic_program()
{
    unsigned int crossover_size = floor(params.population_size * params.crossover_rate);
    unsigned int mutation_size = floor(params.population_size * params.mutation_rate);
    program result;
    thread_pool::instance().start();    

    for(int run = 0; run < params.runs; run++)
    {
        auto begin = chrono::high_resolution_clock::now();

        srand(params.seeds[run]);
        initial_population();
        program best;
        atomic<short> atomic_counter = 0;

        for(int count = 0; count < params.population_size; count++)
        {
            thread_pool::instance().add_job([&,count]{
                population[count].set_fitness(data_set, data_size);

                if(population[count].get_fitness() < best.get_fitness())
                {
                    unique_lock<mutex> lock(mutex_object);
                    
                    if(population[count].get_fitness() < best.get_fitness())
                    {
                        best = population[count];
                    }
                }

                atomic_counter = atomic_counter.load() + 1;
            });
        }

        while(atomic_counter.load() != params.population_size){}

        cout<<"run: "<<run<<endl;
        
        for(int generation = 0; generation < params.generations && best.get_fitness() != 0; generation++)
        {
            unsigned int offspring_counter = 0, crossover_counter = 0, mutation_counter = 0;
            vector<program> new_population(params.population_size);
            
            while(offspring_counter < params.population_size)
            {
                if(crossover_counter < crossover_size)
                {
                    pair<program,program> offspring = crossover(population[select_program()], population[select_program()]);
                    
                    if(!offspring.first.get_root()->is_terminal())
                    {
                        offspring.first.prune(params.offspring_depth);
                        new_population[offspring_counter++] = move(offspring.first);
                        crossover_counter++;
                    }

                    if(offspring_counter < params.population_size && !offspring.second.get_root()->is_terminal())
                    {
                        offspring.second.prune(params.offspring_depth);
                        new_population[offspring_counter++] = move(offspring.second);
                        crossover_counter++;
                    }

                }else
                {
                    program offspring = mutate(population[select_program()]);

                    if(!offspring.get_root()->is_terminal())
                    {
                        offspring.prune(params.offspring_depth);
                        new_population[offspring_counter++] = move(offspring);
                        mutation_counter++;
                    }  
                }
            }

            population = move(new_population);
        
            atomic_counter = 0;

            for(int count = 0; count < params.population_size; count++)
            {
                thread_pool::instance().add_job([&,count]{
                    population[count].set_fitness(data_set, data_size);

                    if(population[count].get_fitness() < best.get_fitness())
                    {
                        unique_lock<mutex> lock(mutex_object);
                        
                        if(population[count].get_fitness() < best.get_fitness())
                        {
                            best = population[count];
                        }
                    }

                    atomic_counter = atomic_counter.load() + 1;
                });
            }

            while(atomic_counter.load() != params.population_size){}

            cout<<endl;
            cout<<"generation: "<<generation + 1<<endl;
            cout<<"best: "<<best.str()<<endl;
            cout<<"height: "<<best.height()<<endl;
            cout<<"fitness: "<<to_string(best.get_fitness())<<endl;
            cout<<endl;
        }

        atomic_counter = 0;

        thread_pool::instance().add_job([&]{
            best.set_root_mean_square_error(data_set, data_size);
            atomic_counter = atomic_counter.load() + 1;
        });

        thread_pool::instance().add_job([&]{
            best.set_mean_absolute_error(data_set, data_size);
            atomic_counter = atomic_counter.load() + 1;
        });

        thread_pool::instance().add_job([&]{
            best.set_median_absolute_error(data_set, data_size);
            atomic_counter = atomic_counter.load() + 1;
        });

        thread_pool::instance().add_job([&]{
            best.set_r_squared(data_set, data_size);
            atomic_counter = atomic_counter.load() + 1;
        });

        while(atomic_counter.load() != 4){}
        
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
        
        program edited = best.edit();
        
        cout<<endl;
        cout<<"generation: "<<params.generations + 1<<endl;
        cout<<"best: "<<best.str()<<endl;
        cout<<"height: "<<best.height()<<endl;
        cout<<"edited: "<<edited.str()<<endl;
        cout<<"edited height: "<<edited.height()<<endl;
        cout<<"runtime: "<<elapsed.count()<<endl;
        cout<<"fitness: "<<to_string(best.get_fitness())<<endl;
        cout<<"root mean square error: "<<to_string(best.get_root_mean_square_error())<<endl;
        cout<<"r squared: "<<to_string(best.get_r_squared())<<endl;
        cout<<"mean absolute error: "<<to_string(best.get_mean_absolute_error())<<endl;
        cout<<"median absolute error: "<<to_string(best.get_median_absolute_error())<<endl;
        cout<<endl;

        if(best.get_fitness() < result.get_fitness())
        {
            result = move(best);
        }
    }

    thread_pool::instance().stop();
    
    return result;
}

Features extract(string sline)
{
    Features result;

    sline.erase(0,sline.find(',') + 1);
    result.duration = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.distance = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_longitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_latitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_longitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_latitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.haversine = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_month = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_day = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_hour = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_minute = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_day_of_week = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_month = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_day = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_hour = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_minute = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_day_of_week = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.temperature = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.precipitation = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.wind_speed = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.humidity = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.solar_radiation = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.snow_fall = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.ground_temperature = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dust_concentration = atof(sline.substr(0,sline.find(',')).c_str());
    
    return result;
}


// COS 700 lecture
// Draft Coach - Google Docs