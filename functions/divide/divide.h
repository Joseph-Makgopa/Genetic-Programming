#ifndef DIVIDE_H
#define DIVIDE_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>

class divide: public primitive
{
    public:
        divide(std::shared_ptr<primitive> left_arg,std::shared_ptr<primitive> right_arg): primitive(2, "divide")
        {
            set_left(left_arg);
            set_right(right_arg);
        }

        divide(): primitive(2, "divide")
        {
            
        }

        void set_left(std::shared_ptr<primitive> left)
        {
            set(0, left);
        } 

        void set_right(std::shared_ptr<primitive> right)
        {
            set(1, right);
        }

        float eval(Features& features)
        {
            if(arguments_size() != 2)
            {
                throw string("Error: "+ to_string(arguments_size()) + " arguments found for binary operator");
            }

            float denominator = get(1)->eval(features);

            return get(0)->eval(features) / (denominator == 0 ? 1 : denominator);
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<divide>(new divide(get(0)->clone(),get(1)->clone()));
        }
};

#endif