#ifndef DROPOFF_DAY_OF_WEEK_H
#define DROPOFF_DAY_OF_WEEK_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_day_of_week: public primitive
{
    private:
        dropoff_day_of_week(): primitive(0, "dropoff_day_of_week")
        {

        }
    public:
        static std::shared_ptr<dropoff_day_of_week> object()
        {
            static std::shared_ptr<dropoff_day_of_week> result = std::shared_ptr<dropoff_day_of_week>(new dropoff_day_of_week());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.dropoff_day_of_week;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_day_of_week";
        }
};

#endif