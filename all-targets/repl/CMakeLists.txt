cmake_minimum_required(VERSION 3.5)
project(Elang)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  #  -g flag to enable debug symbols

file(GLOB_RECURSE SOURCES ../../src/**.cpp)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/builtins/main.cpp")

add_executable(Elang ${SOURCES})
target_include_directories(Elang PRIVATE src)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set_target_properties(Elang PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# Define custom target to run the program
add_custom_target(run COMMAND Elang DEPENDS Elang WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(Elang LLVM)