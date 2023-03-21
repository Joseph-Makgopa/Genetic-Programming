#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class temperature: public primitive
{
    private:
        temperature(): primitive(0, "temperature")
        {

        }
    public:
        static std::shared_ptr<temperature> object()
        {
            static std::shared_ptr<temperature> result = std::shared_ptr<temperature>(new temperature());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.temperature;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "temperature";
        }
};

#endif