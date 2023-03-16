#include "genetic_program.h"

using namespace std;

void genetic_program::generate_population()
{
    population.clear();

    switch(parameters.generation_method)
    {
        case Grow:
        {
            for(int count = 0; count < parameters.population_size; count++)
            {
                program individual;
                individual.build(parameters.max_depth, true);

                population.push_back(individual);
            }
        }break;
        case Full:
        {
            for(int count = 0; count < parameters.population_size; count++)
            {
                program individual;
                individual.build(parameters.max_depth, false);

                population.push_back(individual);
            }
        }break;
        case Ramped_Half_And_Half:
        {
            unsigned int levels = parameters.max_depth - 1;
            unsigned int level_size = floor(parameters.population_size / levels);
            unsigned int build_size = parameters.population_size;
            unsigned int depth = 2;

            while(build_size > 0)
            {

                level_size = level_size * 2 > build_size ? build_size : level_size;
                unsigned int middle = floor(level_size / 2);

                for(int count = 0; count < level_size; count++)
                {
                    program individual;
                    individual.build(parameters.max_depth, count > middle ? false: true);
                    population.push_back(individual);
                }

                build_size -= level_size;
                depth++;
            }
            
        }break;
    }
}

unsigned int genetic_program::select_program()
{
    int random_index = rand() % population.size();
    int result_index = random_index;

    for(int count = 1; count < parameters.tournament_size; count++)
    {
        random_index = rand() % population.size();
        if(population[random_index].get_fitness() > population[result_index].get_fitness())
        {
            result_index = random_index;
        }
    }

    return result_index;
}

pair<program,program> genetic_program::crossover(program parent_one,program parent_two)
{
    program offspring_one(parent_one);
    program offspring_two(parent_two);

    int crossover_index_one = rand() % parent_one.count_nodes();
    int crossover_index_two = rand() % parent_two.count_nodes();

    // cout<<crossover_index_one<<endl;
    // cout<<crossover_index_two<<endl;

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

program genetic_program::mutate(program parent)
{
    program result(parent);
    program segment;

    unsigned int mutation_index = rand() % parent.count_nodes();

    pair<shared_ptr<primitive>, shared_ptr<primitive>> mutation_point = result.get_node(mutation_index);

    segment.build(parameters.mutation_depth,false);

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

void genetic_program::execute()
{
    generate_population();
    vector<program> new_population;

    for(int run = 0; run < parameters.runs; run++)
    {
        unsigned int cutoff = floor(parameters.crossover_rate * parameters.population_size);
        
    }
}