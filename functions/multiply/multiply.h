#ifndef MULTIPLY_H
#define MULTIPLY_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include<memory>

class multiply: public primitive
{
    public:
        multiply(std::shared_ptr<primitive> left_arg, std::shared_ptr<primitive> right_arg): primitive(2, "multiply")
        {
            set_left(left_arg);
            set_right(right_arg);
        }


        multiply(): primitive(2, "multiply")
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

        double eval(Features& features)
        {
            return get(0)->eval(features) * get(1)->eval(features);
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<multiply>(new multiply(get(0)->clone(),get(1)->clone()));
        }
};

#endif