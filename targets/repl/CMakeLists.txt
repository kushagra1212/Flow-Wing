cmake_minimum_required(VERSION 3.5)
project(FlowWing)

set(CMAKE_CXX_STANDARD 17)


# Enable warnings globally
add_compile_options(-Wall -Wextra -Wpedantic)

# Use ccache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Using ccache, found in ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

# Define REPL_TEST_MODE macro based on the build type (`cmake -DTESTS_ENABLED=ON ..`)
if(TESTS_ENABLED)

    # Locate GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    file(GLOB_RECURSE SOURCES ../../src/**.cpp ../../tests/**.cpp)
    add_compile_definitions(REPL_TEST_MODE)
else()
    file(GLOB_RECURSE SOURCES ../../src/**.cpp)
    
    # Remove files in the IR and compiler directories using list(FILTER)
    list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/../../src/IR/.*")
    list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/../../src/compiler/.*")
    add_compile_definitions(REPL_MODE)
endif()

# Set the default executable name
set(DEFAULT_EXECUTABLE_NAME "FlowWing")

# Set the executable name based on whether it's a test build or not
if(TESTS_ENABLED)
    set(EXECUTABLE_NAME "runTests")
else()
    set(EXECUTABLE_NAME "FlowWing")
endif()

# Define platform-specific libraries
if(WIN32)
    set(PLATFORM_LIBS "")
else()
    set(PLATFORM_LIBS pthread)
endif()

# Link the executable with the adjusted name
add_executable(${EXECUTABLE_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/../../src/REPL/Repl.cpp" ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${GTEST_LIBRARIES} ${PLATFORM_LIBS})

# Set the output name of the executable
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${DEFAULT_EXECUTABLE_NAME})

# Add .exe extension on Windows for the executable name
if(WIN32)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES SUFFIX ".exe")
endif()
