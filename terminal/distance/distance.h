#ifndef DISTANCE_H
#define DISTANCE_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class distance: public primitive
{
    private:
        distance():primitive(0, "distance")
        {

        }
    public:
        static std::shared_ptr<distance> object()
        {
            static std::shared_ptr<distance> result = std::shared_ptr<distance>(new distance());
            
            return result;
        }

        double eval(Features& features)
        {
            return features.distance;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "distance";
        }
};

#endif