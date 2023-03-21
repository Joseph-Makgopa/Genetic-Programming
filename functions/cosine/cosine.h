#ifndef cosine_H
#define cosine_H
#include "../../primitive/primitive.h"
#include "../../features/Features.h"
#include <memory>
#include <cmath>

class cosine: public primitive
{
    public:
        cosine(std::shared_ptr<primitive> arg): primitive(1, "cosine")
        {
            set_argument(arg);
        }


        cosine(): primitive(1, "cosine")
        {
            
        }

        void set_argument(std::shared_ptr<primitive> arg)
        {
            set(0, arg);
        }

        double eval(Features& features)
        {
            return cos(get(0)->eval(features));
        }

        shared_ptr<primitive> clone()
        {
            return shared_ptr<cosine>(new cosine(get(0)->clone()));
        }
};

#endif