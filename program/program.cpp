#include "program.h"
#include "../features/Features.h"
#include "../functions/function_store/function_store.h"
#include "../terminal/terminal_store/terminal_store.h"
#include "../terminal/constant/constant.h"
#include <vector>
#include <queue>
#include <cmath>
#include <memory>
#include <algorithm>

using namespace std;

void program::set_fitness(Features* data,unsigned int size)
{
    set_root_mean_square_error(data, size);
    fitness = rmse;
}

void program::set_root_mean_square_error(Features* data, unsigned int data_size)
{
    double squared_error = 0;

    for(int count = 0; count < data_size; count++)
    {
        double estimate = eval(data[count]);
        squared_error += pow(data[count].duration - estimate, 2);
    }

    rmse =  sqrt(squared_error / data_size);
}

void program::set_r_squared(Features* data, unsigned int data_size)
{
    double sample_average = 0;
    double error_sum = 0;
    double mean_deviation = 0;

    for(int count = 0; count < data_size; count++)
    {
        sample_average += data[count].duration;

        double estimate = eval(data[count]);
        error_sum += pow(data[count].duration - estimate, 2);
    }

    sample_average /= data_size;

    for(int count = 0; count < data_size; count++)
    {
        mean_deviation += pow(data[count].duration - sample_average,2);
    }

    r_squared =  1 - (error_sum / mean_deviation);
}

void program::set_median_absolute_error(Features* data, unsigned data_size)
{
    double* absolute_errors = new double[data_size];
    
    for(int count = 0; count < data_size; count++)
    {
        double expected = eval(data[count]);
        absolute_errors[count] = abs(data[count].duration - expected);
    }

    sort(absolute_errors, absolute_errors + data_size);

    int middle_index = data_size / 2;

    medae =  data_size % 2 == 1 ? absolute_errors[middle_index] : (absolute_errors[middle_index - 1] + absolute_errors[middle_index]) / 2;
}

void program::set_mean_absolute_error(Features* data, unsigned data_size)
{
    double error_sum = 0;

    for(int count = 0; count < data_size; count++)
    {
        double estimate = eval(data[count]);
        error_sum += abs(data[count].duration - estimate);
    }

    mae =  error_sum / data_size;
}

shared_ptr<primitive> program::edit_helper(shared_ptr<primitive> node)
{
    if(node->is_terminal())
    {
        return node;
    }

    bool constants = true;
    bool same_arguments = true;
    bool zero_argument = true;

    for(int count = 0; count < node->arguments_size(); count++)
    {
        shared_ptr<primitive> sub_tree = edit_helper(node->get(count));
        node->set(count, sub_tree);

        if(!sub_tree->is_terminal() || sub_tree->get_name().find("constant") == string::npos)
        {
            constants = false;
        }
        
        if(!sub_tree->is_terminal() || sub_tree->str() != "constant(0)")
        {
            zero_argument = false;
        }

        if(!sub_tree->is_terminal() || node->get(0)->get_name() != sub_tree->get_name())
        {
            same_arguments = false;
        }
    }

    if(constants == true)
    {
        Features temp;
        return shared_ptr<constant>(constant::object(node->eval(temp)));
    }

    if(zero_argument == true)
    {
        if(node->get_name() == "multiply")
        {
            return shared_ptr<constant>(constant::object(0));
        }

        if(node->get_name() == "divide" && node->get(0)->str() == "constant(0)")
        {
            return shared_ptr<constant>(constant::object(0));
        }
    }

    if(same_arguments == true)
    {
        if(node->get_name() == "subtract")
        {
            return shared_ptr<constant>(constant::object(0));
        }

        if(node->get_name() == "divide")
        {
            return shared_ptr<constant>(constant::object(1));
        }
    }

    return node;
}

program program::edit()
{
    program result(*this);

    if(result.root.use_count() != 0)
    {
        result.root = edit_helper(result.root);
    }

    return result;
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

    if(root.use_count() == 0)
    {
        return 0;
    }

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

void program::prune(unsigned int depth)
{
    if(depth < 2)
    {
        return;
    }

    queue<pair<unsigned int, shared_ptr<primitive>>> q;

    q.push(make_pair(1,root));
    pair<unsigned int, shared_ptr<primitive>> current;

    while(!q.empty())
    {
        current = q.front();
        q.pop();
        
        if(current.first + 1 == depth)
        {
            for(int count = 0; count < current.second->arguments_size(); count++)
            {
                shared_ptr<primitive> temp = current.second->get(count);
                
                if(temp->is_terminal())
                {
                    continue;
                }

                while(!temp->is_terminal())
                {
                    temp = temp->get(rand() % temp->arguments_size());
                }

                current.second->set(count, temp);
            }
        }else
        {
            for(shared_ptr<primitive>& child: current.second->get_arguments())
            {
                q.push(make_pair(current.first + 1, child));
            }
        }
    }
}

unsigned int program::height()
{
    if(root.use_count() == 0)
    {
        return 0;
    }

    queue<pair<unsigned int, shared_ptr<primitive>>> q;

    q.push(make_pair(1,root));
    pair<unsigned int, shared_ptr<primitive>> current;
    unsigned int result = 1;

    while(!q.empty())
    {
        current = q.front();
        q.pop();

        if(current.first > result)
        {
            result = current.first;
        }

        for(shared_ptr<primitive>& arg: current.second->get_arguments())
        {
            q.push(make_pair(current.first + 1, arg));
        }
    }

    return result;
}