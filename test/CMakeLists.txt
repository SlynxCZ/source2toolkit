cmake_minimum_required(VERSION 3.18)
project(source2toolkit_test CXX)

set(CMAKE_CXX_STANDARD 20)

set(S2TK_ROOT $ENV{SOURCE2TOOLKIT})

if (NOT S2TK_ROOT)
    message(FATAL_ERROR "SOURCE2TOOLKIT env variable not set")
endif()

add_subdirectory(${S2TK_ROOT}/vendor/source2toolkit-sdk source2toolkit-sdk-consumer)

add_s2toolkit_plugin(source2toolkit_test main.cpp)