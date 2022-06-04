#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <boost/json/value.hpp>
#include <string>

class course {
   public:
    course();

    std::string get_valute();
    void set_valute(const std::string& valute);
    bool check_valute() const;

    void refresh();

    float get_course() const;

   private:
    std::string curl_data;
    boost::json::value parsed_data;

    std::string url;
    std::string valute;
};

#endif
