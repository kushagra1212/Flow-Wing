cmake_minimum_required(VERSION 3.5)
 project(tests)
 
set(CMAKE_CXX_STANDARD 17)
# Locate GTest
find_package(GTest REQUIRED)

file(GLOB_RECURSE SOURCES ../src/**.cpp ../tests/**.cpp )
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")
add_executable(main IORedirectionTest.cpp test_main.cpp)
# Add Google Test
add_subdirectory(gtest)
include_directories($/usr/include  gtest)




add_executable(tests ${SOURCES})
include_directories(${GTEST_INCLUDE_DIRS})
target_include_directories(tests PRIVATE src)
target_link_libraries(tests gtest gtest_main)

# Link runTests with what we want to test and the GTest and pthread library


target_link_libraries(tests ${GTEST_LIBRARIES} pthread)  
add_custom_target(runTests COMMAND tests DEPENDS tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR}) 