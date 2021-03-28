project(geographiclib_usage_example)
cmake_minimum_required(VERSION 3.10)

find_package(GeographicLib REQUIRED)

add_executable(geo_test1 geographiclib_example.cpp)
target_link_libraries(geo_test1 ${GeographicLib_LIBRARIES})

add_executable(convert_test convert_test.cpp)
target_link_libraries(convert_test ${GeographicLib_LIBRARIES})
