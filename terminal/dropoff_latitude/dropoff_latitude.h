#ifndef DROPOFF_LATITUDE_H
#define DROPOFF_LATITUDE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_latitude: public primitive
{
    private:
        dropoff_latitude(): primitive(0, "dropoff_latitude")
        {

        }
    public:
        static std::shared_ptr<dropoff_latitude> object()
        {
            static std::shared_ptr<dropoff_latitude> result = std::shared_ptr<dropoff_latitude>(new dropoff_latitude());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.dropoff_latitude;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_latitude";
        }
};

#endif