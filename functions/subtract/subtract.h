#ifndef SUBTRACT_H
#define SUBTRACT_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>

class subtract: public primitive
{
    public:
        subtract(std::shared_ptr<primitive> left_arg, std::shared_ptr<primitive> right_arg): primitive(2, "subtract")
        {
            set_left(left_arg);
            set_right(right_arg);
        }

        subtract(): primitive(2, "subtract")
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
            return get(0)->eval(features) - get(1)->eval(features);
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<subtract>(new subtract(get(0)->clone(),get(1)->clone()));
        }
};

#endif