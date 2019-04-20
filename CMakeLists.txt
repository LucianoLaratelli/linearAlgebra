cmake_minimum_required(VERSION 3.14)
project(matrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(matrix main.cpp matrix.cpp vector.cpp)

find_package(Catch2 REQUIRED)
add_executable(tests test.cpp matrix.cpp vector.cpp)
target_link_libraries(tests Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(tests)
