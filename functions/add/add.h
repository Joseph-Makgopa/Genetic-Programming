#ifndef ADD_H
#define ADD_H
#include "../../primitive/primitive.h"
#include "../../features/features.h"
#include <memory>

class add: public primitive
{
    public:
        add(std::shared_ptr<primitive> left_arg, std::shared_ptr<primitive> right_arg): primitive(2, "add")
        {
            set_left(left_arg);
            set_right(right_arg);
        }

        add(): primitive(2, "add")
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
            return get(0)->eval(features) + get(1)->eval(features);
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<add>(new add(get(0)->clone(),get(1)->clone()));
        }
};

#endif