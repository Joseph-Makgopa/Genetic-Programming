#ifndef HAVERSINE_H
#define HAVERSINE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class haversine: public primitive
{
    private:
        haversine(): primitive(0, "haversine")
        {

        }
    public:
        static std::shared_ptr<haversine> object()
        {
            static std::shared_ptr<haversine> result = std::shared_ptr<haversine>(new haversine());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.haversine;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "haversine";
        }
};

#endif