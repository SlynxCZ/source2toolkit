cmake_minimum_required(VERSION 3.18)
project(source2toolkit_test CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../vendor/source2toolkit-sdk source2toolkit-sdk-consumer)
add_s2toolkit_plugin(source2toolkit_test main.cpp)