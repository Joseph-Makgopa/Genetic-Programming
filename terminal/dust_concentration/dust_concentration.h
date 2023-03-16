#ifndef DUST_CONCENTRATION_H
#define DUST_CONCENTRATION_H
#include "../../primitive/primitive.h"
#include <string>
#include <memory>

class dust_concentration: public primitive
{
    private:
        dust_concentration(): primitive(0, "dust_concentration")
        { 

        }
    public:
        static std::shared_ptr<dust_concentration> object()
        {
            static std::shared_ptr<dust_concentration> result = std::shared_ptr<dust_concentration>(new dust_concentration());
            
            return result;
        }

        float eval(Features& features)
        {
            return features.dust_concentration;
        }

        shared_ptr<primitive> clone()
        {
            return object();
        }

        inline string str() const
        {
            return "dust_concentration";
        }
};

#endif