#ifndef DROPOFF_MONTH_H
#define DROPOFF_MONTH_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dropoff_month: public primitive
{
    private:
        dropoff_month(): primitive(0, "dropoff_month")
        {

        }
    public:
        static std::shared_ptr<dropoff_month> object()
        {
            static std::shared_ptr<dropoff_month> result = std::shared_ptr<dropoff_month>(new dropoff_month());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.dropoff_month;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dropoff_month";
        }
};

#endif