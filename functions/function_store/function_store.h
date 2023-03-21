#ifndef FUNCTION_STORE_H
#define FUNCTION_STORE_H
#include <memory>
#include <vector>
#include "../../primitive/primitive.h"
#include "../divide/divide.h"
#include "../subtract/subtract.h" 
#include "../add/add.h"
#include "../multiply/multiply.h"
#include "../logarithm/logarithm.h"
#include "../cosine/cosine.h"
#include "../sine/sine.h"
#include "../exponential/exponential.h"

using namespace std;

class function_store
{
    private:
        function_store()
        {

        }
    public:
        static shared_ptr<function_store> object()
        {
            static shared_ptr<function_store> instance = shared_ptr<function_store>(new function_store());

            return instance;
        }

        shared_ptr<primitive> get(int sub)
        {
            shared_ptr<primitive> result = make_shared<add>();

            switch(sub)
            {
                case 1:{
                    result = make_shared<subtract>();
                }break;
                case 2:{
                    result = make_shared<divide>();
                }break;
                case 3:{
                    result = make_shared<multiply>();
                }break;
                case 4:{
                    result = make_shared<logarithm>();
                }break;
                case 5:{
                    result = make_shared<sine>();
                }break;
                case 6:{
                    result = make_shared<cosine>();
                }break;
                case 7:{
                    result = make_shared<exponential>();
                }break;
            }

            return result;
        }

        vector<shared_ptr<primitive>> get_all()
        { 
            return {
                make_shared<subtract>(),
                make_shared<add>(),
                make_shared<multiply>(),
                make_shared<divide>(),
                make_shared<logarithm>(),
                make_shared<sine>(),
                make_shared<cosine>(),
                make_shared<exponential>()
            };
        }


};

#endif