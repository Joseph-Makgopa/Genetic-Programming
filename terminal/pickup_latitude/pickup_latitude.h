#ifndef PICKUP_LATITUDE_H
#define PICKUP_LATITUDE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_latitude: public primitive
{
    private:
        pickup_latitude(): primitive(0, "pickup_latitude")
        {

        }
    public:
        static std::shared_ptr<pickup_latitude> object()
        {
            static std::shared_ptr<pickup_latitude> result = std::shared_ptr<pickup_latitude>(new pickup_latitude());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.pickup_latitude;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "pickup_latitude";
        }
};

#endif