#ifndef PICKUP_LONGITUDE_H
#define PICKUP_LONGITUDE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_longitude: public primitive
{
    private:
        pickup_longitude(): primitive(0, "pickup_longitude")
        {

        }
    public:
        static std::shared_ptr<pickup_longitude> object()
        {
            static std::shared_ptr<pickup_longitude> result = std::shared_ptr<pickup_longitude>(new pickup_longitude());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.pickup_longitude;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "pickup_longitude";
        }
};

#endif