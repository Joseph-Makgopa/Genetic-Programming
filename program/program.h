#ifndef PROGRAM_H
#define PROGRAM_H
#include "../primitive/primitive.h"
#include "../features/Features.h"
#include "../functions/function_store/function_store.h"
#include "../terminal/terminal_store/terminal_store.h"
#include <memory>
#include <cstdlib>
#include <iostream>

class program{
private:
    std::shared_ptr<primitive> root;
    float fitness;
    void grow_method(shared_ptr<primitive>& parent,unsigned short depth);
    void full_method(shared_ptr<primitive>& parent,unsigned short depth);

    inline int select_random(const vector<shared_ptr<primitive>>& primitives)
    {
        return rand() % primitives.size();
    }
public: 
    program(): fitness(-1)
    {
        
    }

    program(const program& right)
    {
        root = right.root->clone();
        fitness = right.fitness;
    }

    program(const program&& right)
    {
        root = move(right.root);
        fitness = right.fitness;
    }

    void set_root(shared_ptr<primitive> arg)
    {
        root = arg;
    }

    shared_ptr<primitive> get_root() const
    {
        return root;
    }

    float get_fitness() const
    {
        return fitness;
    }

    unsigned int count_nodes();

    pair<shared_ptr<primitive>, shared_ptr<primitive>> get_node(unsigned int index);

    float eval(Features& features)
    {
        if(root.use_count() != 0)
        {
            return root->eval(features);
        }

        return 0;
    }

    program operator=(const program& right)
    {
        root = right.root->clone();
        fitness = right.fitness;

        return *this;
    }

    program operator=(const program&& right)
    {
        if(this != &right)
        {
            root = right.root->clone();
            fitness = right.fitness;
        }

        return *this;
    }

    void set_fitness(vector<Features>& data,float bound);

    void build(unsigned int max_depth,bool grow);

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