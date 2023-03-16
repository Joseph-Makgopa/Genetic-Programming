#ifndef DROPOFF_DAY_H
#define DROPFF_DAY_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_day: public primitive
{
    private:
        dropoff_day():primitive(0, "dropoff_day")
        {

        }
    public:
        static std::shared_ptr<dropoff_day> object()
        {
            static std::shared_ptr<dropoff_day> result = std::shared_ptr<dropoff_day>(new dropoff_day());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.dropoff_day;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_day";
        }
};

#endif