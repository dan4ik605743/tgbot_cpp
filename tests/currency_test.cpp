#include <boost/test/unit_test.hpp>

#include "currency/currency.hpp"

BOOST_AUTO_TEST_SUITE(currency_test)

BOOST_AUTO_TEST_CASE(currency_test) {
    course course;
    course.set_valute("USD");
    course.refresh();

    BOOST_TEST(course.get_course() != 0);
}

BOOST_AUTO_TEST_SUITE_END()
