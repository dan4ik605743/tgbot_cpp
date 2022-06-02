find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost 1.76.0 REQUIRED COMPONENTS system program_options locale REQUIRED)

include_directories(
    ${OPENSSL_INCLUDE_DIR} 
    ${Boost_INCLUDE_DIR}
)

add_executable(
    ${PROJECT_NAME} 
    main.cpp 
    network/network.cpp 
    weather/weather.cpp
    currency/currency.cpp
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE TgBot
    ${CMAKE_THREAD_LIBS_INIT} 
    ${OPENSSL_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${CURL_LIBRARIES}
)
