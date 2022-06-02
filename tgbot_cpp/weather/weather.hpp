#ifndef WEATHER_CPP
#define WEATHER_CPP

#include <boost/json/value.hpp>
#include <string>

class weather {
   public:
    weather(const std::string& api);

    std::string get_city();
    void set_city(const std::string& city);
    bool check_city();

    void refresh();

    std::string get_weather();
    int get_temp();
    float get_wind();

   private:
    std::string curl_data;
    boost::json::value parsed_data;

    std::string api;
    std::string url;
    std::string city;
};

#endif
