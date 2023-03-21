#ifndef SNOW_FALL_H
#define SNOW_FALL_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class snow_fall: public primitive
{
    private:
        snow_fall(): primitive(0, "snow_fall")
        {

        }
    public:
        static std::shared_ptr<snow_fall> object()
        {
            static std::shared_ptr<snow_fall> result = std::shared_ptr<snow_fall>(new snow_fall());
             
            return result;
        }

        double eval(Features& features)
        {
            return features.snow_fall;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "snow_fall";
        }
};

#endif