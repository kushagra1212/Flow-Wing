cmake_minimum_required(VERSION 3.5)
project(elang)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(elang ${SOURCES})
target_include_directories(elang PRIVATE src)

set_target_properties(elang PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# Define custom target to run the program
add_custom_target(run COMMAND elang DEPENDS elang WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


