cmake_minimum_required(VERSION 3.0)

project(algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB SRCS "src/*.cc")
add_library(algo ${SRCS})

add_subdirectory(test)
