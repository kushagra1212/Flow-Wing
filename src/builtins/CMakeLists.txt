cmake_minimum_required(VERSION 3.5)
project(BuiltIns)

set(CMAKE_CXX_STANDARD 17)


find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})


add_executable(BuiltIns "main.cpp" "BuiltinFunctions.cpp")
target_link_libraries(BuiltIns LLVM)