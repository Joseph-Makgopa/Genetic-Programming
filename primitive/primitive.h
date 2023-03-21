#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "../features/Features.h"
#include <memory>
#include <vector>

using namespace std;

class primitive{
    private:
        vector<shared_ptr<primitive>> arguments;
        unsigned int max_arguments;
        string name;
    public:
        primitive(unsigned int arguments_length, string name): name(name), max_arguments(arguments_length)
        {
            arguments = vector<shared_ptr<primitive>>(arguments_length);
        }

        bool is_terminal()
        {
            return arguments.size() == 0;
        } 

        shared_ptr<primitive>& get(int sub)
        {
            return arguments[sub];
        }

        void set(int sub, shared_ptr<primitive> value)
        {
            arguments[sub] = value;
        }

        int arguments_size() const
        {
            return arguments.size();
        }

        inline int get_max_arguments() const
        {
            return max_arguments;
        }

        inline void set_name(string str)
        {
            name = str;
        }

        inline string get_name() const
        {
            return name;
        }

        void add_argument(shared_ptr<primitive> arg)
        {
            arguments.push_back(arg);
        }

        virtual shared_ptr<primitive> clone()=0;

        virtual double eval(Features&)=0;

        virtual string str() const
        {
            string result =  name + "( ";

            for(int count = 0; count < arguments.size(); count++)
            {
                result += arguments[count]->str();

                if( count != arguments.size() - 1)
                    result += ", ";
            }

            return result + " )";
        }
};



#endif