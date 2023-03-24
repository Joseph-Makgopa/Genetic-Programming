#ifndef CONSTANT_H
#define CONSTANT_H
#include "../../primitive/primitive.h"
#include <string>
#include <iostream>
#include <memory>

class constant: public primitive
{
    private:
        unsigned short value;
        constant():primitive(0, "constant")
        {
            value = rand() % 10;
            set_name("constant(" + to_string(value) + ")");
        }

        constant(int val):value(val),primitive(0,"constant")
        {
            set_name("constant(" + to_string(val) + ")");
        }
    public:
        static std::shared_ptr<constant> object()
        {
            return std::shared_ptr<constant>(new constant());;
        }

        static std::shared_ptr<constant> object(int val)
        {
            return std::shared_ptr<constant>(new constant(val));;
        }

        double eval(Features& )
        {
            return value;
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<constant>(new constant(value));
        }

        inline string str() const
        {
            return get_name();
        }
};

#endif