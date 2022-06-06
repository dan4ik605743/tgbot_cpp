#include <boost/test/unit_test.hpp>

#include "course/course.hpp"

BOOST_AUTO_TEST_SUITE(course_test)

BOOST_AUTO_TEST_CASE(course_test) {
    course course;
    course.set_valute("USD");
    course.refresh();

    BOOST_TEST(course.get_course() != 0);
}

BOOST_AUTO_TEST_SUITE_END()
