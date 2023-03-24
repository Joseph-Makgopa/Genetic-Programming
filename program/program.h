#ifndef PROGRAM_H
#define PROGRAM_H
#include "../primitive/primitive.h"
#include "../features/Features.h"
#include "../functions/function_store/function_store.h"
#include "../terminal/terminal_store/terminal_store.h"
#include <memory>
#include <cstdlib>
#include <iostream>
#include <limits>

class program{
private:
    std::shared_ptr<primitive> root;
    double fitness;
    double rmse;
    double r_squared;
    double mae;
    double medae;
    void grow_method(shared_ptr<primitive>& parent,unsigned short depth);
    void full_method(shared_ptr<primitive>& parent,unsigned short depth);

    inline int select_random(const vector<shared_ptr<primitive>>& primitives)
    {
        return rand() % primitives.size();
    }

    shared_ptr<primitive> edit_helper(shared_ptr<primitive> node);
public: 
    program(): fitness(numeric_limits<double>::max()), 
        rmse(numeric_limits<double>::max()), 
            r_squared(numeric_limits<double>::max()),
                mae(numeric_limits<double>::max()),
                    medae(numeric_limits<double>::max())
    {
        
    }

    program(const program& right)
    {
        root = right.root->clone();
        fitness = right.fitness;
        rmse = right.rmse;
        r_squared = right.r_squared;
        mae = right.mae;
        medae = right.medae;
    }

    program(const program&& right)
    {
        root = move(right.root);
        fitness = right.fitness;
        rmse = right.rmse;
        r_squared = right.r_squared;
        mae = right.mae;
        medae = right.medae;
    }

    void clean()
    {
        root.reset();
        fitness = numeric_limits<double>::max(); 
        rmse = numeric_limits<double>::max();
        r_squared = numeric_limits<double>::max();
        mae = numeric_limits<double>::max();
        medae = numeric_limits<double>::max();
    }

    void prune(unsigned int depth);

    void set_root(shared_ptr<primitive> arg)
    {
        root = arg;
    }

    shared_ptr<primitive> get_root() const
    {
        return root;
    }

    double get_fitness() const
    {
        return fitness;
    }

    double get_root_mean_square_error() const
    {
        return rmse;
    }

    double get_r_squared() const
    {
        return r_squared;
    }

    double get_median_absolute_error() const
    {
        return medae;
    }

    double get_mean_absolute_error() const
    {
        return mae;
    }

    unsigned int count_nodes();

    unsigned int height();

    pair<shared_ptr<primitive>, shared_ptr<primitive>> get_node(unsigned int index);

    double eval(Features& features)
    {
        if(root.use_count() != 0)
        {
            return root->eval(features);
        }

        return 0;
    }

    void set_root_mean_square_error(Features* data, unsigned int data_size);

    void set_r_squared(Features* data, unsigned int data_size);

    void set_median_absolute_error(Features* data, unsigned data_size);

    void set_mean_absolute_error(Features* data, unsigned data_size);

    program operator=(const program& right)
    {
        root = right.root->clone();
        fitness = right.fitness;
        rmse = right.rmse;
        r_squared = right.r_squared;
        mae = right.mae;
        medae = right.medae;

        return *this;
    }

    program operator=(const program&& right)
    {
        if(this != &right)
        {
            root = move(right.root);
            fitness = right.fitness;
            rmse = right.rmse;
            r_squared = right.r_squared;
            mae = right.mae;
            medae = right.medae;
        }

        return *this;
    }

    void set_fitness(Features* data,unsigned int size);

    void build(unsigned int max_depth,bool grow);

    program edit();

    string str() const
    {
        
        if(root.use_count() != 0)
        {

            return root->str();
        }

        return "";
    }
};

#endif