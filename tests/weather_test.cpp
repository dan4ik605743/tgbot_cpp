#include <boost/test/unit_test.hpp>

#include "weather/weather.hpp"

BOOST_AUTO_TEST_SUITE(weather_test)

BOOST_AUTO_TEST_CASE(weather_test) {
    weather weather("07c25c1d34c8154a333c3d61865dcb21");
    weather.set_city("Красноярск");
    weather.refresh();

    BOOST_TEST(weather.get_weather() != "");
}

BOOST_AUTO_TEST_SUITE_END()
