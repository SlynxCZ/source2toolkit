cmake_minimum_required(VERSION 3.18)
project(source2toolkit C CXX ASM)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SPDLOG_HEADER_ONLY ON CACHE BOOL "" FORCE)
set(FMT_WERROR OFF CACHE BOOL "" FORCE)

function(resolve_dep_internal OUT_VAR ENV_NAME)
    if (DEFINED ENV{${ENV_NAME}} AND NOT "$ENV{${ENV_NAME}}" STREQUAL "")
        file(TO_CMAKE_PATH "$ENV{${ENV_NAME}}" _resolved)
        set(${OUT_VAR} "${_resolved}" PARENT_SCOPE)
        message(STATUS "${ENV_NAME} -> ${_resolved}")
    else ()
        message(FATAL_ERROR "${ENV_NAME} is not set")
    endif ()
endfunction()

resolve_dep_internal(SOURCE2TOOLKIT_SDK_DIR SOURCE2TOOLKIT_SDK)
resolve_dep_internal(METAMOD_DIR MMSOURCE_DEV)

# core build
set(SOURCE2TOOLKIT_CORE ON CACHE BOOL "" FORCE)
add_subdirectory(${SOURCE2TOOLKIT_SDK_DIR} ${CMAKE_BINARY_DIR}/source2toolkit-sdk)

# SourceHook comes from the SDK above, which builds it and links it into
# everything that uses it -- building it here as well would be the second copy.

add_subdirectory(vendor/dynlibutils)
add_subdirectory(vendor/spdlog)

file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        src/*.h
        src/*.hpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_compile_definitions(source2toolkit-sdk PUBLIC SOURCE2TOOLKIT_CORE)

if (DEFINED ENV{GITHUB_SHA_SHORT} AND NOT "$ENV{GITHUB_SHA_SHORT}" STREQUAL "")
    add_definitions(-DGITHUB_SHA="$ENV{GITHUB_SHA_SHORT}")
else ()
    add_definitions(-DGITHUB_SHA="Local")
endif ()

if (DEFINED ENV{SEMVER} AND NOT "$ENV{SEMVER}" STREQUAL "")
    add_definitions(-DSEMVER="$ENV{SEMVER}")
else ()
    add_definitions(-DSEMVER="Local")
endif ()

include(${CMAKE_CURRENT_LIST_DIR}/makefiles/metamod/configure_metamod.cmake)

find_package(Git QUIET)
if (GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_SHA
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )
else ()
    set(GIT_SHA "nogit")
endif ()

if (UNIX AND NOT APPLE)
    SET(source2toolkit_include_directories
            ${CMAKE_SOURCE_DIR}/src
            ${METAMOD_DIR}/core
            ${CMAKE_SOURCE_DIR}/vendor
            ${CMAKE_SOURCE_DIR}/vendor/dynlibutils/include
            ${CMAKE_SOURCE_DIR}/vendor/dynlibutils/include/dynlibutils
            ${CMAKE_SOURCE_DIR}/vendor/openssl/include
            ${CMAKE_SOURCE_DIR}/vendor/mysql/include
            ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    )
    SET(source2toolkit_link_libraries
            ${CMAKE_SOURCE_DIR}/vendor/mysql/lib/libmysqlclient.a
            ${CMAKE_SOURCE_DIR}/vendor/openssl/lib/linux/libssl.a
            ${CMAKE_SOURCE_DIR}/vendor/openssl/lib/linux/libcrypto.a
            dynlibutils
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            PREFIX ""
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/addons/source2toolkit/bin/linuxsteamrt64"
    )
elseif (WIN32)
    SET(source2toolkit_include_directories
            ${CMAKE_SOURCE_DIR}/src
            ${METAMOD_DIR}/core
            ${CMAKE_SOURCE_DIR}/vendor
            ${CMAKE_SOURCE_DIR}/vendor/dynlibutils/include
            ${CMAKE_SOURCE_DIR}/vendor/dynlibutils/include/dynlibutils
            ${CMAKE_SOURCE_DIR}/vendor/openssl/include
            ${CMAKE_SOURCE_DIR}/vendor/mysql/include
            ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    )
    SET(source2toolkit_link_libraries
            ${CMAKE_SOURCE_DIR}/vendor/mysql/lib/mysqlclient.lib
            ${CMAKE_SOURCE_DIR}/vendor/openssl/lib/windows/ssl.lib
            ${CMAKE_SOURCE_DIR}/vendor/openssl/lib/windows/crypto.lib
            crypt32.lib
            dynlibutils
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            PREFIX ""
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/addons/source2toolkit/bin/win64"
    )
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ${source2toolkit_include_directories})
target_include_directories(source2toolkit-sdk PUBLIC ${source2toolkit_include_directories})

target_link_libraries(${PROJECT_NAME}
        source2toolkit-config
        source2toolkit-sdk
        ${source2toolkit_link_libraries}
)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/configs ${CMAKE_BINARY_DIR}
)
