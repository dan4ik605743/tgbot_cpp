find_package (Boost 1.75.0 REQUIRED COMPONENTS unit_test_framework REQUIRED)
find_package(CURL)

enable_testing()

set(
    SRC_LIST
    main.cpp
    weather_test.cpp
    currency_test.cpp
    network_test.cpp
    ../tgbot_cpp/network/network.cpp 
    ../tgbot_cpp/weather/weather.cpp
    ../tgbot_cpp/currency/currency.cpp
)

set(
    LIB_LIST
    ${Boost_LIBRARIES} 
    ${CURL_LIBRARIES}
)

include_directories(
    ../tgbot_cpp
    ${Boost_INCLUDE_DIR}
)

add_executable(
    ${PROJECT_NAME}_test
    ${SRC_LIST}
)

target_link_libraries(
    ${PROJECT_NAME}_test
    ${LIB_LIST}
)

add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
