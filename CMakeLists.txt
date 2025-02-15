cmake_minimum_required(VERSION 3.10)

project(SIMPDP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include/)

file(GLOB SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB INCL ${CMAKE_SOURCE_DIR}/include/*.hpp)

add_executable(SIMPDP ${SRCS} ${INCL})


