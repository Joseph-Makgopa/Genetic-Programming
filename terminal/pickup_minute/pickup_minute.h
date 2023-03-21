#ifndef PICKUP_MINUTE_H
#define PICKUP_MINUTE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_minute: public primitive
{
    private:
        pickup_minute(): primitive(0, "pickup_minute")
        {

        }
    public:
        static std::shared_ptr<pickup_minute> object()
        {
            static std::shared_ptr<pickup_minute> result = std::shared_ptr<pickup_minute>(new pickup_minute());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.pickup_minute;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "pickup_minute";
        }
};

#endif