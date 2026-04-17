cmake_minimum_required(VERSION 3.18)
project(source2toolkit_test CXX)

set(CMAKE_CXX_STANDARD 20)

set(S2TK_SDK $ENV{S2TK_SDK})

if (NOT S2TK_SDK)
    message(FATAL_ERROR "S2TK_SDK env variable not set")
endif()

add_subdirectory(${S2TK_SDK} source2toolkit-sdk-consumer)

add_s2toolkit_plugin(source2toolkit_test main.cpp)