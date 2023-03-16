#ifndef SOLAR_RADIATION_H
#define SOLAR_RADIATION_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class solar_radiation: public primitive
{
    private:
        solar_radiation(): primitive(0, "solar_radiation")
        {

        }
    public:
        static std::shared_ptr<solar_radiation> object()
        {
            static std::shared_ptr<solar_radiation> result = std::shared_ptr<solar_radiation>(new solar_radiation());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.solar_radiation;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }
        
        inline string str() const
        {
            return "solar_radiation";
        }
};

#endif