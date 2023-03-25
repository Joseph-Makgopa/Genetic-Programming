#ifndef SQUARE_H
#define SQUARE_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>
#include <cmath>

class square: public primitive
{
    public:
        square(std::shared_ptr<primitive> arg): primitive(1, "square")
        {
            set_argument(arg);
        }


        square(): primitive(1, "square")
        {
            
        }

        void set_argument(std::shared_ptr<primitive> arg)
        {
            set(0, arg);
        }

        double eval(Features& features)
        {
            return sqrt(get(0)->eval(features));
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<square>(new square(get(0)->clone()));
        }
};

#endif