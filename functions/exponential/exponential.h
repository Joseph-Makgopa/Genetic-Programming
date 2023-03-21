#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>
#include <cmath>

class exponential: public primitive
{
    public:
        exponential(std::shared_ptr<primitive> arg): primitive(1, "exp")
        {
            set_argument(arg);
        }


        exponential(): primitive(1, "exp")
        {
            
        }

        void set_argument(std::shared_ptr<primitive> arg)
        {
            set(0, arg);
        }

        double eval(Features& features)
        {
            return exp(get(0)->eval(features));
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<exponential>(new exponential(get(0)->clone()));
        }
};

#endif