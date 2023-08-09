cmake_minimum_required(VERSION 3.5)
project(ElangTest)

set(CMAKE_CXX_STANDARD 17)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE SOURCES ../../src/**.cpp)

# remove main.cpp from sources

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/main.cpp")

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/compiler/Compiler.cpp")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests "${CMAKE_CURRENT_SOURCE_DIR}/../../tests/test_main.cpp" ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)