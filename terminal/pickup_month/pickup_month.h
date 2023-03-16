#ifndef PICKUP_MONTH_H
#define PICKUP_MONTH_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class pickup_month: public primitive
{
    private:
        pickup_month(): primitive(0, "pickup_month")
        {

        }
    public:
        static std::shared_ptr<pickup_month> object()
        {
            static std::shared_ptr<pickup_month> result = std::shared_ptr<pickup_month>(new pickup_month());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.pickup_month;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }
        
        inline string str() const
        {
            return "pickup_month";
        }
};

#endif