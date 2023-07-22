cmake_minimum_required(VERSION 3.5)
project(elang)

set(CMAKE_CXX_STANDARD 17)

# Add the source files for the main executable
file(GLOB_RECURSE SOURCES src/**.cpp)

# Create the main executable target
add_executable(elang ${SOURCES})
target_include_directories(elang PRIVATE src)

# Set properties for the elang target
set_target_properties(elang PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# Add any additional libraries needed for the main executable
# For example, if you have other libraries, you can link them here
# target_link_libraries(elang PRIVATE your_library_name)

# Define custom target to run the program
add_custom_target(run COMMAND elang DEPENDS elang WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


# --------------------------------------------------------------
# Add test executable target and link with Google Test libraries

# Add the source files for the test executable
file(GLOB_RECURSE TEST_SOURCES tests/**.cpp)

# Create the test executable target
add_executable(tests ${TEST_SOURCES})

# Set properties for the tests target
set_target_properties(tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

# Add Google Test include directories
target_include_directories(tests PRIVATE test)

# Link the test executable with Google Test libraries
target_link_libraries(tests PRIVATE gtest gtest_main)

# Register the test as a CTest
add_test(NAME AllTests COMMAND tests)
