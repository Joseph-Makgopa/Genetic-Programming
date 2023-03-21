#ifndef PICKUP_HOUR_H
#define PICKUP_HOUR_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_hour: public primitive
{
    private:
        pickup_hour(): primitive(0, "pickup_hour")
        {

        }
    public:
        static std::shared_ptr<pickup_hour> object()
        {
            static std::shared_ptr<pickup_hour> result = std::shared_ptr<pickup_hour>(new pickup_hour());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.pickup_hour;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "pickup_hour";
        }
};

#endif