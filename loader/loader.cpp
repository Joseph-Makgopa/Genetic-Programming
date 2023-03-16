#include "loader.h"
#include "../features/Features.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Features loader::extract(string sline)
{
    Features result;

    sline.erase(0,sline.find(',') + 1);
    result.duration = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.distance = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_longitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_latitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_longitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_latitude = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.haversine = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_month = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_day = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_hour = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_minute = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.pickup_day_of_week = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_month = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_day = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_hour = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_minute = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dropoff_day_of_week = atoi(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.temperature = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.precipitation = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.wind_speed = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.humidity = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.solar_radiation = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.snow_fall = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.ground_temperature = atof(sline.substr(0,sline.find(',')).c_str());

    sline.erase(0,sline.find(',') + 1);
    result.dust_concentration = atof(sline.substr(0,sline.find(',')).c_str());

    return result;
}

void loader::load(bool binary_format)
{
    if(binary_format)
    {
        fstream file("dataset/binary_data/data.dat",ios::binary | ios::in);

        if(file.fail())
        {
            throw string("Error: Failed to open file");
        }else
        {
            data.clear();
            Features entry;

            while(!file.eof()){
                file.read((char*)&entry,sizeof(Features));

                data.push_back(entry);
            }

            file.close();
        }
        
    }else
    {
        fstream file("dataset/text_data/data.csv",ios::in);

        if(file.fail())
        {
            throw string("Error: Failed to load data.");
        }else
        {
            data.clear();
            string sline = "";
            getline(file,sline,'\n');

            while(!file.eof())
            {
                getline(file,sline,'\n');

                if(sline == "")
                    continue;

                data.push_back(extract(sline));
            }

            file.close();
        }
    }
}

vector<Features> loader::load(data_type type)
{
    vector<Features> result;
    bool binary_format = true;
    fstream file;

    switch(type)
    {
        case Valid:{
            file.open("dataset/binary_data/valid.dat",ios::binary | ios::in);
        }break;
        case Train:{
            file.open("dataset/binary_data/train.dat",ios::binary | ios::in);
        }break;
        case Test:{
            file.open("dataset/binary_data/test.dat",ios::binary | ios::in);
        }break;
    }

    if(!file.fail())
    {
        
        while(!file.eof())
        {
            Features entry;
            file.read((char*)&entry,sizeof(Features));
            result.push_back(entry);
        }

        file.close();
    }else
    {
        file.clear();

        switch(type)
        {
            case Valid:{
                file.open("dataset/text_data/valid.txt");
            }break;
            case Train:{
                file.open("dataset/text_data/train.txt");
            }break;
            case Test:{
                file.open("dataset/text_data/test.txt");
            }break;
        }

        if(file.fail())
        {
            throw string("Error: Failed to open file '" + to_string(type) + "'");
        }else
        {
            string sline;

            while(!file.eof())
            {
                getline(file, sline, '\n');
                            
                result.push_back(extract(sline));
                file.close();
            }
        }
    }

    return result;
}

void loader::save(bool binary_format)
{
    if(binary_format)
    {
        fstream valid_file("dataset/binary_data/valid.dat",ios::binary | ios::out);
        fstream train_file("dataset/binary_data/train.dat",ios::binary | ios::out);
        fstream test_file("dataset/binary_data/test.dat",ios::binary | ios::out);

        unsigned int upper_bound = floor(data.size() * valid_perc);
        unsigned int lower_bound = 0;

        for(; lower_bound <= upper_bound; lower_bound++) 
        {
            valid_file.write((char*)&data[lower_bound],sizeof(Features));
        }

        upper_bound = floor(data.size() * (valid_perc + train_perc));

        for(; lower_bound <= upper_bound; lower_bound++)
        {
            train_file.write((char*)&data[lower_bound],sizeof(Features));
        }

        for(; lower_bound < data.size(); lower_bound++)
        {
            test_file.write((char*)&data[lower_bound],sizeof(Features));
        }

        valid_file.close();
        train_file.close();
        test_file.close();

    }else
    {
        fstream valid_file("dataset/text_data/valid.txt",ios::out);
        fstream train_file("dataset/text_data/train.txt",ios::out);
        fstream test_file("dataset/text_data/test.txt",ios::out);

        unsigned int upper_bound = floor(data.size() * valid_perc);
        unsigned int lower_bound = 0;

        for(; lower_bound <= upper_bound; lower_bound++) 
        {
            valid_file<<lower_bound<<","<<data[lower_bound].to_line()<<endl;
        }

        upper_bound = floor(data.size() * (valid_perc + train_perc));

        for(unsigned int count = 0; lower_bound <= upper_bound; lower_bound++, count++)
        {
            train_file<<count<<","<<data[lower_bound].to_line()<<endl;
        }

        for(unsigned int count = 0; lower_bound < data.size(); lower_bound++, count++)
        {
            test_file<<count<<","<<data[lower_bound].to_line()<<endl;
        }

        valid_file.close();
        train_file.close();
        test_file.close();
    }
}

void loader::save()
{
    fstream file("dataset/binary_data/data.dat",ios::binary | ios::out);

    for(Features& features: data)
    {
        file.write((char*)&features,sizeof(Features));
    }

    file.close();
}