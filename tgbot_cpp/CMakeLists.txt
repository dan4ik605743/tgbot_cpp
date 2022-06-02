find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system program_options locale REQUIRED)
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

include_directories(
    ${OPENSSL_INCLUDE_DIR} 
    ${Boost_INCLUDE_DIR}
)

add_executable(
    ${PROJECT_NAME} 
    main.cpp 
    network/network.cpp 
    weather/weather.cpp
    course/course.cpp
)

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE TgBot
    ${CMAKE_THREAD_LIBS_INIT} 
    ${OPENSSL_LIBRARIES} 
    ${Boost_LIBRARIES} 
    ${CURL_LIBRARIES}
)
