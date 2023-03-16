#include "Features.h"
#include <string>

using namespace std;

string Features::to_str() const{

    string result = "{\n";

    result += "\tduration = " +  to_string(duration) + ", \n";
    result += "\tdistance = " +  to_string(distance) + ", \n";
    result += "\tpickup_longitude = " +  to_string(pickup_longitude) + ", \n";
    result += "\tpickup_latitude = " +  to_string(pickup_latitude) + ", \n";
    result += "\tdropoff_longitude = " +  to_string(dropoff_longitude) + ", \n";
    result += "\tdropoff_latitude = " +  to_string(dropoff_latitude) + ", \n";
    result += "\thaversine = " + to_string(haversine) + ", \n";
    result += "\tpickup_month = " + to_string(pickup_month) + ", \n";
    result += "\tpickup_day = " + to_string(pickup_day) + ", \n";
    result += "\tpickup_hour = " + to_string(pickup_hour) + ", \n";
    result += "\tpickup_minute = " + to_string(pickup_minute) + ", \n";
    result += "\tpickup_day_of_week = " + to_string(pickup_day_of_week) + ", \n";
    result += "\tdropoff_month = " + to_string(dropoff_month) + ", \n";
    result += "\tdropoff_day = " + to_string(dropoff_day) + ", \n";
    result += "\tdropoff_hour = " + to_string(dropoff_hour) + ", \n";
    result += "\tdropoff_minute = " + to_string(dropoff_minute) + ", \n";
    result += "\tdropoff_day_of_week = " + to_string(dropoff_day_of_week) + ", \n";
    result += "\ttemperature = " + to_string(temperature) + ", \n";
    result += "\tprecipitation = " + to_string(precipitation) + ", \n";
    result += "\twind_speed = " + to_string(wind_speed) + ", \n";
    result += "\thumudity = " + to_string(humidity) + ", \n";
    result += "\tsolar_radiation = " + to_string(solar_radiation) + ", \n";
    result += "\tsnow_fall = " + to_string(snow_fall) + ", \n";
    result += "\tground_temperature = " + to_string(ground_temperature) + ", \n";
    result += "\tdust_concentration = " + to_string(dust_concentration) + ", \n}";

    return result;
}

string Features::to_line() const
{
    string result = "";

    result += to_string(duration) + ",";
    result += to_string(distance) + ",";
    result += to_string(pickup_longitude) + ",";
    result += to_string(pickup_latitude) + ",";
    result += to_string(dropoff_longitude) + ",";
    result += to_string(dropoff_latitude) + ",";
    result += to_string(haversine) + ",";
    result += to_string(pickup_month) + ",";
    result += to_string(pickup_day) + ",";
    result += to_string(pickup_hour) + ",";
    result += to_string(pickup_minute) + ",";
    result += to_string(pickup_day_of_week) + ",";
    result += to_string(dropoff_month) + ",";
    result += to_string(dropoff_day) + ",";
    result += to_string(dropoff_hour) + ",";
    result += to_string(dropoff_minute) + ",";
    result += to_string(dropoff_day_of_week) + ",";
    result += to_string(temperature) + ",";
    result += to_string(precipitation) + ",";
    result += to_string(wind_speed) + ",";
    result += to_string(humidity) + ",";
    result += to_string(solar_radiation) + ",";
    result += to_string(snow_fall) + ",";
    result += to_string(ground_temperature) + ",";
    result += to_string(dust_concentration);

    return result;
}