#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include "loader/loader.h"
#include "Features/Features.h"
#include "program/program.h"
#include "functions/function_store/function_store.h"
#include "genetic_program/genetic_program.h"

using namespace std;

class check{
    public:
        check(int val)
        {

        }

        check(check& other)
        {
            cout<<"copy"<<endl;
        }

        check(check&& other)
        {
            cout<<"move"<<endl;
        }
};

int main()
{
    loader data_loader;
    algorithm_parameters param;
    param.max_depth = 5;
    param.population_size = 10;
    param.tournament_size = 4;
    param.mutation_depth = 2;
    param.generation_method = Ramped_Half_And_Half;

    genetic_program gp(param, data_loader);
    srand(time(0));

    program individual;

    individual.build(3,false);

    cout<<individual.str()<<endl;

    return 0;
}