#include "weather.hpp"
#include "network/network.hpp"

#include <boost/json.hpp>

weather::weather(const std::string& api) {
    this->api = api;
}

std::string weather::get_city() {
    return boost::json::value_to<std::string>(parsed_data.at("name"));
}

void weather::set_city(const std::string& city) {
    this->city = city;

    url =
        "http://api.openweathermap.org/data/2.5/"
        "weather?q=" +
        city + "&appid=" + api + "&lang=ru";
}

bool weather::check_city() {
    if (parsed_data.at("cod").is_int64()) {
        return true;
    } else {
        return false;
    }
}

void weather::refresh() {
    curl_data = get_request(url);
    parsed_data = boost::json::parse(curl_data);
}

std::string weather::get_weather() {
    return boost::json::value_to<std::string>(
        parsed_data.at("weather").at(0).at("description"));
}

int weather::get_temp() {
    // kelvin_to_celsius
    return (boost::json::value_to<float>(parsed_data.at("main").at("temp"))) -
           273;
}

float weather::get_wind() {
    return boost::json::value_to<float>(parsed_data.at("wind").at("speed"));
}
