#ifndef PRECIPITATION_H
#define PRECIPITATION_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class precipitation: public primitive
{
    private:
        precipitation(): primitive(0, "precipitation")
        {

        }
    public:
        static std::shared_ptr<precipitation> object()
        {
            static std::shared_ptr<precipitation> result = std::shared_ptr<precipitation>(new precipitation());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.precipitation;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "precipitation";
        }
};

#endif