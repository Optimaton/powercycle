cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(powercycle-mgr)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(
  powercycle
  ${SOURCES}
)
