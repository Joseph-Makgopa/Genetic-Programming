#ifndef TERMINAL_STORE_H
#define TERMINAL_STORE_H
#include <memory>
#include <vector>
#include "../../primitive/primitive.h"
#include "../distance/distance.h"
#include "../pickup_longitude/pickup_longitude.h"
#include "../pickup_latitude/pickup_latitude.h"
#include "../dropoff_longitude/dropoff_longitude.h"
#include "../dropoff_latitude/dropoff_latitude.h"
#include "../haversine/haversine.h"
#include "../pickup_month/pickup_month.h"
#include "../pickup_day/pickup_day.h"
#include "../pickup_hour/pickup_hour.h"
#include "../pickup_minute/pickup_minute.h"
#include "../pickup_day_of_week/pickup_day_of_week.h"
#include "../dropoff_month/dropoff_month.h"
#include "../dropoff_day/dropoff_day.h"
#include "../dropoff_hour/dropoff_hour.h"
#include "../dropoff_minute/dropoff_minute.h"
#include "../dropoff_day_of_week/dropoff_day_of_week.h"
#include "../temperature/temperature.h"
#include "../precipitation/precipitation.h"
#include "../snow_fall/snow_fall.h"
#include "../solar_radiation/solar_radiation.h"
#include "../humudity/humudity.h"
#include "../ground_temperature/ground_temperature.h"
#include "../dust_concentration/dust_concentration.h"
#include "../constant/constant.h"

using namespace std;

class terminal_store
{
    private:
        vector<shared_ptr<primitive>> terminals = {
            distance::object(),
            pickup_longitude::object(),
            pickup_latitude::object(),
            dropoff_longitude::object(),
            dropoff_latitude::object(),
            haversine::object(),
            pickup_month::object(),
            pickup_day::object(),
            pickup_hour::object(),
            pickup_minute::object(),
            pickup_day_of_week::object(),
            dropoff_month::object(),
            dropoff_day::object(),
            dropoff_hour::object(),
            dropoff_minute::object(),
            dropoff_day_of_week::object(),
            temperature::object(),
            precipitation::object(),
            humudity::object(),
            snow_fall::object(),
            solar_radiation::object(),
            ground_temperature::object(),
            dust_concentration::object()
        };

        terminal_store()
        {

        }
    public:
        static shared_ptr<terminal_store> object()
        {
            static shared_ptr<terminal_store> instance = shared_ptr<terminal_store>(new terminal_store());

            return instance;
        }

        shared_ptr<primitive> get(int sub) const
        {
            return terminals[sub];
        }

        shared_ptr<primitive> get(string name) const
        {
            for(shared_ptr<primitive> value:terminals)
            {
                if(value->get_name() == name)
                {
                    return value;
                }
            }

            return terminals[0];
        }

        vector<shared_ptr<primitive>> get_all()
        {
            vector<shared_ptr<primitive>> result = terminals;
            result.push_back(constant::object());

            return result;
        }

        int size() const
        {
            return terminals.size();
        }

};

#endif
