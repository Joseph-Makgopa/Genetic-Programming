#ifndef DROPOFF_MINUTE_H
#define DROPOFF_MINUTE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_minute: public primitive
{
    private:
        dropoff_minute(): primitive(0, "dropoff_minute")
        {

        }
    public:
        static std::shared_ptr<dropoff_minute> object()
        {
            static std::shared_ptr<dropoff_minute> result = std::shared_ptr<dropoff_minute>(new dropoff_minute());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.dropoff_minute;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_minute";
        }
};

#endif