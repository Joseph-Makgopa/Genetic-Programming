#ifndef GENETIC_PROGRAM
#define GENETIC_PROGRAM
#include "../program/program.h"
#include "../features/Features.h"
#include "../loader/loader.h"
#include <cmath>

using namespace std;

enum generation_method
{
    Grow = 0,
    Full = 1,
    Ramped_Half_And_Half = 2
};

struct algorithm_parameters
{
    vector<unsigned int> seeds;
    unsigned int runs;
    unsigned int generations;
    unsigned int max_depth;
    unsigned int population_size;
    unsigned int tournament_size;
    unsigned int mutation_depth;
    double crossover_rate;
    generation_method generation_method;
    double bound;
};

class genetic_program
{
    private:
        algorithm_parameters parameters;
        vector<program> population;
        vector<Features> data;
    public:
        genetic_program(algorithm_parameters parameters): parameters(parameters)
        {

        }

        genetic_program(algorithm_parameters parameters,loader data_loader): parameters(parameters)
        {
            data = data_loader.load(Valid);
        }

        vector<program> get_population() const
        {
            return population;
        }

        void generate_population();

        unsigned int select_program();

        pair<program,program> crossover(program parent_one,program parent_two);

        program mutate(program parent);

        void execute();
};

#endif