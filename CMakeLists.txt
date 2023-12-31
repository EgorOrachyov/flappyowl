cmake_minimum_required(VERSION 3.0)
project(flappyowl)

###########################################################
# global cxx setup
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

###########################################################
# Define platform
#  - WINDOWS = Windows Desktop
#  - MACOSX  = MacOS X
#  - LINUX   = Linux

set(TARGET_WINDOWS NO)
set(TARGET_LINUX NO)
set(TARGET_MACOS NO)
set(TARGET_DEFINES)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(TARGET_WINDOWS YES)
    list(APPEND TARGET_DEFINES TARGET_WINDOWS)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(TARGET_LINUX YES)
    list(APPEND TARGET_DEFINES TARGET_LINUX)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(TARGET_MACOS YES)
    list(APPEND TARGET_DEFINES TARGET_MACOS)
else ()
    message(FATAL_ERROR "Unsupported target platform")
endif ()

###########################################################
# Define build type

if (CMAKE_BUILD_TYPE MATCHES Debug)
    list(APPEND TARGET_DEFINES WG_DEBUG)
    message(STATUS "Build project in debug mode (specified)")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    list(APPEND TARGET_DEFINES WG_RELEASE)
    message(STATUS "Build project in release mode (specified)")
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    list(APPEND TARGET_DEFINES WG_DEBUG_RELEASE)
    message(STATUS "Build project in release mode with debug info (specified)")
else ()
    list(APPEND TARGET_DEFINES WG_RELEASE)
    message(STATUS "Build project in release mode (default, not specified)")
endif ()

###########################################################
# Aux functions to work with targets

function(wmoge_target_defs target)
    foreach (DEFINITION ${TARGET_DEFINES})
        target_compile_definitions(${target} PUBLIC ${DEFINITION})
    endforeach ()
endfunction()

###########################################################
# third-party dependencies of the tutorial

add_subdirectory(deps)

###########################################################
# engine sources

add_subdirectory(engine)

###########################################################
# actual flappy owl game sources

add_subdirectory(game)
