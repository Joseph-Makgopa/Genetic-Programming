#ifndef FEATURES_H
#define FEATURES_H
#include <string>
#include <iostream>
#include <fstream>

class Features
{
    public:
        int duration, distance;
        float pickup_longitude, pickup_latitude, dropoff_longitude, dropoff_latitude;
        float haversine;
        int pickup_month, pickup_day, pickup_hour, pickup_minute, pickup_day_of_week;
        int dropoff_month, dropoff_day, dropoff_hour, dropoff_minute, dropoff_day_of_week;
        float temperature, precipitation, wind_speed, humidity, solar_radiation, snow_fall;
        float ground_temperature, dust_concentration;

        Features()
        {
            duration = distance = 0;
            pickup_longitude = pickup_latitude =  dropoff_longitude =  dropoff_latitude = 0;
            haversine = 0;
            pickup_month = pickup_day = pickup_hour = pickup_minute = pickup_day_of_week = 0;
            dropoff_month = dropoff_day = dropoff_hour = dropoff_minute = dropoff_day_of_week = 0;
            temperature = precipitation = wind_speed = humidity = solar_radiation = snow_fall = 0;
            ground_temperature = dust_concentration = 0;
        }

        std::string to_str() const;

        std::string to_line() const;

        void save_text(std::fstream& file, unsigned int index) const;    
};  

#endif
