#ifndef HUMUDITY_H
#define HUMUDITY_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class humudity: public primitive
{
    private:
        humudity(): primitive(0, "humudity")
        {

        }
    public:
        static std::shared_ptr<humudity> object()
        {
            static std::shared_ptr<humudity> result = std::shared_ptr<humudity>(new humudity());
            
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
            return "humudity";
        }
};

#endif