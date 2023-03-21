#ifndef PICKUP_DAY_H
#define PICKUP_DAY_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_day: public primitive
{
    private:
        pickup_day(): primitive(0, "pickup_day")
        {

        }
    public:
        static std::shared_ptr<pickup_day> object()
        {
            static std::shared_ptr<pickup_day> result = std::shared_ptr<pickup_day>(new pickup_day());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.pickup_day;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "pickup_day";
        }
};

#endif