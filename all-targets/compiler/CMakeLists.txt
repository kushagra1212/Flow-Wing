cmake_minimum_required(VERSION 3.5)
project(ElangCompiler)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  #  -g flag to enable debug symbols

file(GLOB_RECURSE SOURCES ../../src/**.cpp)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/main.cpp")
add_executable(ElangCompiler ${SOURCES})
target_include_directories(ElangCompiler PRIVATE src)


# Define custom target to run the program
add_custom_target(run COMMAND ElangCompiler DEPENDS ElangCompiler WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
