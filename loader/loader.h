#ifndef LOADER_H
#define LOADER_H
#include <vector>
#include "../features/Features.h"
#include <fstream>
#include <cmath>

using namespace std;

enum data_type
{
    Valid = 0,
    Train = 2,
    Test = 3
};

class loader
{
    private:
        vector<Features> data;
        float valid_perc;
        float train_perc;
        float test_perc;
    public:
        loader()
        {
            valid_perc = 0.1;
            train_perc = 0.6;
            test_perc = 0.2;
        }

        void set_sizing(float valid, float train, float test)
        {
            valid_perc = valid;
            train_perc = train;
            test_perc = test;
        }

        Features extract(string line);

        vector<Features> load(data_type type);

        void load(bool binary_format);

        void save(bool binary_format);

        void save();
        
        inline unsigned int get_size() const
        {
            return data.size();
        }

        inline unsigned int valid_size() const
        {
            return floor(data.size() * valid_perc);
        }

        inline unsigned int train_size() const
        {
            return floor(data.size() * train_perc);
        }

        inline unsigned int test_size() const
        {
            return floor(data.size() * test_perc);
        }
};


#endif