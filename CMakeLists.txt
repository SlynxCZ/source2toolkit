cmake_minimum_required(VERSION 3.18)
project(source2toolkit C CXX ASM)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif ()

set(FMT_WERROR OFF CACHE BOOL "" FORCE)

set(METAMOD_DIR vendor/metamod-source)

add_subdirectory(vendor/source2toolkit-sdk)
add_subdirectory(vendor/spdlog)

file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        src/*.h
        src/*.hpp
)

list(APPEND SOURCE_FILES
        vendor/dynlibutils/module.cpp
        vendor/dynlibutils/module.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

if (DEFINED ENV{GITHUB_SHA_SHORT})
    add_definitions(-DGITHUB_SHA="$ENV{GITHUB_SHA_SHORT}")
else ()
    add_definitions(-DGITHUB_SHA="Local")
endif ()

if (DEFINED ENV{SEMVER})
    add_definitions(-DSEMVER="$ENV{SEMVER}")
else ()
    add_definitions(-DSEMVER="Local")
endif ()

include(${CMAKE_CURRENT_LIST_DIR}/makefiles/metamod/configure_metamod.cmake)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${METAMOD_DIR}/core
        ${METAMOD_DIR}/third_party/khook/include
        vendor/spdlog/include
        vendor
)

find_package(Git QUIET)
if (GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_SHA
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )
else()
    set(GIT_SHA "nogit")
endif()

if (LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            PREFIX ""
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/addons/source2toolkit/bin/linuxsteamrt64"
    )
elseif (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            PREFIX ""
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/addons/source2toolkit/bin/win64"
    )
endif()

target_link_libraries(${PROJECT_NAME}
        source2toolkit-config
        source2toolkit-sdk
        spdlog
)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/configs ${CMAKE_BINARY_DIR}
)
