cmake_minimum_required(VERSION 3.1)

project(fcryptor)

find_package(Boost REQUIRED)

find_library(BOOST_FILESYSTEM boost_filesystem)
find_library(BOOST_PROGRAM_OPTIONS boost_program_options)

file(GLOB SRC_PATHS src/*.cpp)
set (SOURCES ${SRC_PATHS})

set (CMAKE_CXX_STANDART 1z)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1z")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${BOOST_FILESYSTEM} ${BOOST_PROGRAM_OPTIONS})