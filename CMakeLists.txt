cmake_minimum_required(VERSION 3.0)

project(algorithms)

include_directories(include)

file(GLOB SRCS "src/*.cc")
add_library(algo ${SRCS})

add_subdirectory(test)
