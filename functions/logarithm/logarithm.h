#ifndef LOGARITHM_H
#define LOGARITHM_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>
#include <cmath>

class logarithm: public primitive
{
    public:
        logarithm(std::shared_ptr<primitive> arg): primitive(1, "log")
        {
            set_argument(arg);
        }


        logarithm(): primitive(1, "log")
        {
            
        }

        void set_argument(std::shared_ptr<primitive> arg)
        {
            set(0, arg);
        }

        double eval(Features& features)
        {
            double argument = get(0)->eval(features);

            return argument == 0 ? 0 : log10(abs(argument));
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<logarithm>(new logarithm(get(0)->clone()));
        }
};

#endif