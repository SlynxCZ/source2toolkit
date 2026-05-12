cmake_minimum_required(VERSION 3.18)
project(source2toolkit_test CXX)

set(CMAKE_CXX_STANDARD 20)

set(PLUGIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/addons/source2toolkit/plugins")
set(SOURCE2TOOLKIT_SDK $ENV{SOURCE2TOOLKIT_SDK})

if (NOT SOURCE2TOOLKIT_SDK)
    message(FATAL_ERROR "SOURCE2TOOLKIT_SDK env variable not set")
endif()

add_subdirectory(${SOURCE2TOOLKIT_SDK} ${CMAKE_BINARY_DIR}/source2toolkit-sdk)

target_include_directories(source2toolkit-sdk PUBLIC ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        src/*.h
        src/*.hpp
)

add_s2toolkit_plugin(source2toolkit_test ${SOURCE_FILES})

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/configs ${CMAKE_BINARY_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})