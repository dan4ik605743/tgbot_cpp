#ifndef COURSE_HPP
#define COURSE_HPP

#include <boost/json/value.hpp>
#include <string>

class course {
   public:
    course();

    void set_valute(const std::string& valute);
    bool check_valute();

    void refresh();

    float get_course();

   private:
    std::string curl_data;
    boost::json::value parsed_data;

    std::string url;
    std::string valute;
};

#endif
