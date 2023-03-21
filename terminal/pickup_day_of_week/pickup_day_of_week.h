#ifndef PICKUP_DAY_OF_WEEK_H
#define PICKUP_DAY_OF_WEEK_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_day_of_week: public primitive
{
    private:
        pickup_day_of_week(): primitive(0, "pickup_day_of_week")
        {

        }
    public:
        static std::shared_ptr<pickup_day_of_week> object()
        {
            static std::shared_ptr<pickup_day_of_week> result = std::shared_ptr<pickup_day_of_week>(new pickup_day_of_week());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.pickup_day_of_week;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "pickup_day_of_week";
        }
};

#endif