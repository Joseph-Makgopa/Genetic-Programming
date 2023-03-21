#ifndef DROPOFF_LONGITUDE_H
#define DROPOFF_LONGITUDE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_longitude: public primitive
{
    private:
        dropoff_longitude(): primitive(0, "dropoff_longitude")
        {

        }
    public:
        static std::shared_ptr<dropoff_longitude> object()
        {
            static std::shared_ptr<dropoff_longitude> result = std::shared_ptr<dropoff_longitude>(new dropoff_longitude());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.dropoff_longitude;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_longitude";
        }
};

#endif