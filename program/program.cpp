#include "program.h"
#include "../features/Features.h"
#include "../functions/function_store/function_store.h"
#include "../terminal/terminal_store/terminal_store.h"
#include <vector>
#include <queue>
#include <cmath>
#include <memory>
#include <algorithm>

using namespace std;

void program::set_fitness(vector<Features>& data,float bound)
{
    int hit = 0;

    for(Features& features: data)
    {
        float value = eval(features);
        value = abs(value - features.duration);
        
        if(value <= bound)
        {
            hit++;
        }
    }

    fitness = float(hit) / data.size();
}

void program::build(unsigned int max_depth,bool grow)
{
    root.reset();

    if(grow == false)
    {
        vector<shared_ptr<primitive>> fstore =  function_store::object()->get_all();
        root = fstore[select_random(fstore)];
        full_method(root,max_depth - 1);
    }else{
        vector<shared_ptr<primitive>> fstore =  function_store::object()->get_all();
        root = fstore[select_random(fstore)];
        grow_method(root,max_depth - 1);
    }
}

void program::grow_method(shared_ptr<primitive>& parent,unsigned short depth)
{
    if(depth == 1)
    {
        vector<shared_ptr<primitive>> tstore = terminal_store::object()->get_all();
        
        for(int count = 0; count < parent->get_max_arguments(); count++)
        {
            shared_ptr<primitive> child = tstore[select_random(tstore)];
            parent->set(count, child);
        }
    }else
    {
        for(int count = 0; count < parent->get_max_arguments(); count++)
        {
            vector<shared_ptr<primitive>> fstore = function_store::object()->get_all();
            vector<shared_ptr<primitive>> tstore = terminal_store::object()->get_all();
            vector<shared_ptr<primitive>> store(fstore.size() + tstore.size());
            
            merge(fstore.begin(), fstore.end(), tstore.begin(), tstore.end(), store.begin());

            shared_ptr<primitive> child = store[select_random(store)];
            parent->set(count, child);

            if(!child->is_terminal())
            {
                grow_method(child, depth - 1);
            }
        }
    }        
}

void program::full_method(shared_ptr<primitive>& parent,unsigned short depth)
{
    if(depth == 1)
    {
        vector<shared_ptr<primitive>> tstore = terminal_store::object()->get_all();
        
        for(int count = 0; count < parent->get_max_arguments(); count++)
        {
            shared_ptr<primitive> child = tstore[select_random(tstore)];
            parent->set(count, child);
        }
    }else
    {
        for(int count = 0; count < parent->get_max_arguments(); count++)
        {
            vector<shared_ptr<primitive>> fstore = function_store::object()->get_all();
            shared_ptr<primitive> child = fstore[select_random(fstore)];

            parent->set(count, child);

            full_method(child, depth - 1);
        }
    }
}

unsigned int program::count_nodes()
{
    queue<shared_ptr<primitive>> node_queue;
    unsigned int result = 0;

    node_queue.push(root);

    while(!node_queue.empty())
    {
        shared_ptr<primitive>& temp = node_queue.front();
        node_queue.pop();
        result++;

        for(int count = 0; count < temp->arguments_size(); count++)
        {
            node_queue.push(temp->get(count));    
        }
    }

    return result;
}

pair<shared_ptr<primitive>, shared_ptr<primitive>> program::get_node(unsigned int index)
{
    queue<pair<shared_ptr<primitive>, shared_ptr<primitive>>> node_queue;
    pair<shared_ptr<primitive>, shared_ptr<primitive>> result = make_pair(shared_ptr<primitive>(),root);
    node_queue.push(make_pair(shared_ptr<primitive>(),root));

    while(!node_queue.empty())
    {
        pair<shared_ptr<primitive>, shared_ptr<primitive>> temp = node_queue.front();
        node_queue.pop();

        if(index == 0)
        {
            result = temp;
            break;
        }

        for(int count = 0; count < temp.second->arguments_size(); count++)
        {
            node_queue.push(make_pair(temp.second,temp.second->get(count)));    
        }

        index--;
    }

    if(index != 0)
    {
        throw string("Error: Index out of bound");
    }

    return result;
}