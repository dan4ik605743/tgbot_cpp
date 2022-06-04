#include "currency.hpp"
#include "network/network.hpp"

#include <boost/json.hpp>

course::course() {
    url = "https://www.cbr-xml-daily.ru/daily_json.js";
}

std::string course::get_valute() {
    return valute;
}

void course::set_valute(const std::string& valute) {
    this->valute = valute;
}

bool course::check_valute() const {
    try {
        boost::json::value_to<std::string>(
            parsed_data.at("Valute").at(valute).at("ID"));
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void course::refresh() {
    curl_data = get_request(url);
    parsed_data = boost::json::parse(curl_data);
}

float course::get_course() const {
    return boost::json::value_to<float>(
        parsed_data.at("Valute").at(valute).at("Value"));
}
