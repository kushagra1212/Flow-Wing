cmake_minimum_required(VERSION 3.5)
project(ElangTest)

set(CMAKE_CXX_STANDARD 17)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
file(GLOB_RECURSE SOURCES ../../src/**.cpp ../../tests/**/**.cpp)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/just-in-time-compiler/JITCompiler.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/builtins/main.cpp")
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Conditionally define TEST_MODE macro based on the build type
if(TESTS_ENABLED)
    add_compile_definitions(TEST_MODE)
endif()


# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests "${CMAKE_CURRENT_SOURCE_DIR}/../../src/REPL/Repl.cpp" ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread LLVM)