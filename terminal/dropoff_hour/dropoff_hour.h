#ifndef DROPOFF_HOUR_H
#define DROPOFF_HOUR_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_hour: public primitive
{
    private:
        dropoff_hour(): primitive(0, "dropoff_hour")
        {

        }
    public:
        static std::shared_ptr<dropoff_hour> object()
        {
            static std::shared_ptr<dropoff_hour> result = std::shared_ptr<dropoff_hour>(new dropoff_hour());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.dropoff_hour;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_hour";
        }
};

#endif