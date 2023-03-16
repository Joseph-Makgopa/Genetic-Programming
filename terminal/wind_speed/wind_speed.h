#ifndef WINDSPEED_H
#define WINDSPEED_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class wind_speed: public primitive
{
    private:
        wind_speed(): primitive(0, "wind_speed")
        {

        }
    public:
        static std::shared_ptr<wind_speed> object()
        {
            static std::shared_ptr<wind_speed> result = std::shared_ptr<wind_speed>(new wind_speed());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.wind_speed;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "wind_speed";
        }
};

#endif