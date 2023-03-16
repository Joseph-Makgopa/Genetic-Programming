#ifndef GROUND_TEMPERATURE_H
#define GROUND_TEMPERATURE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class ground_temperature: public primitive
{
    private:
        ground_temperature(): primitive(0, "ground_temperature")
        {

        }
    public:
        static std::shared_ptr<ground_temperature> object()
        {
            static std::shared_ptr<ground_temperature> result = std::shared_ptr<ground_temperature>(new ground_temperature());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.ground_temperature;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "ground_temperature";
        }
};

#endif