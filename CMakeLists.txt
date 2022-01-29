cmake_minimum_required(VERSION 3.10)
project(pwm_test)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE INCLUDES "")
file(GLOB_RECURSE SOURCES  "")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
SET(CMAKE_CXX_FLAGS "-O3 -j")

 #   add_library(pigpio SHARED IMPORTED)

add_executable(main "main.c" ${SOURCES} ${INCLUDES})

find_package(pigpio REQUIRED pigpiod_if2)
find_library(pigpio_location pigpiod_if2  PATH_SUFFIXES pigpiod_if2)
#find_library(pigpio_location NAMES libpigpio.so)
message(STATUS ${pigpio_location})
find_path(PIGPIO_HEADER_PATH pigpiod_if2.h PATH_SUFFIXES pigpiod_if2)
target_include_directories(main PUBLIC ${PIGPIO_HEADER_PATH})

add_library(pigpio SHARED IMPORTED)

# Provide the full path to the library, so CMake knows where to find it.
set_target_properties(pigpio PROPERTIES IMPORTED_LOCATION ${pigpio_location})
target_link_libraries(main PRIVATE pigpiod_if2 pthread rt)
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main)
