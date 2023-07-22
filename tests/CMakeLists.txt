cmake_minimum_required(VERSION 3.5)
 project(ElangTest)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE SOURCES ../src/**.cpp)

# remove main.cpp from sources

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")


# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test_main.cpp ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)