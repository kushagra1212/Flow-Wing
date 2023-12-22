cmake_minimum_required(VERSION 3.5)
project(FlowWing)

set(CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(LLVM_DIR "/usr/lib/llvm-16/share/llvm/cmake")

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})


# use ccache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Using ccache, found in ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

# Conditionally define REPL_TEST_MODE macro based on the build type (`cmake -DTESTS_ENABLED=ON ..`)
if(TESTS_ENABLED)
    file(GLOB_RECURSE SOURCES ../../src/**.cpp ../../tests/**.cpp)
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/builtins/main.cpp")
    add_compile_definitions(REPL_TEST_MODE)
else()
    file(GLOB_RECURSE SOURCES ../../src/**.cpp)   
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/builtins/main.cpp")
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

# Link the executable with the adjusted name
add_executable(${EXECUTABLE_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/../../src/REPL/Repl.cpp" ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} ${GTEST_LIBRARIES} pthread LLVM)

# Set the output name of the executable
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${DEFAULT_EXECUTABLE_NAME})
