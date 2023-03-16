#ifndef SINE_H
#define SINE_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>
#include <cmath>

class sine: public primitive
{
    public:
        sine(std::shared_ptr<primitive> arg): primitive(1, "sine")
        {
            set_argument(arg);
        }


        sine(): primitive(1, "sine")
        {
            
        }

        void set_argument(std::shared_ptr<primitive> arg)
        {
            set(0, arg);
        }

        float eval(Features& features)
        {
            return sin(get(0)->eval(features));
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<sine>(new sine(get(0)->clone()));
        }
};

#endif