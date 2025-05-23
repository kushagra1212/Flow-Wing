cmake_minimum_required(VERSION 3.22.1)
cmake_policy(SET CMP0075 NEW)
project(FlowWing VERSION 0.0.1)
set(VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 17)



# Add a custom target for version information
add_custom_target(version
    COMMAND ${CMAKE_COMMAND} -DVERSION=${VERSION} -P ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake
    COMMENT "Generating version information"
)

# Add find_package calls for ZLIB and Zstandard (zstd)
find_package(ZLIB REQUIRED)
find_package(zstd REQUIRED)


# Check for ZLIB
if (NOT ZLIB_FOUND)
    message(FATAL_ERROR "ZLIB not found. Please install ZLIB to proceed.")
endif()

# Check for zstd
if (NOT zstd_FOUND)
    message(FATAL_ERROR "Zstandard (zstd) not found. Please install zstd to proceed.")
endif()


# Find the LLVM libraries statically
find_package(LLVM REQUIRED CONFIG)
# Check if LLVM variables are populated
message(STATUS "LLVM_FOUND: ${LLVM_FOUND}")
message(STATUS "LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_DEFINITIONS: ${LLVM_DEFINITIONS}")
message(STATUS "LLVM_VERSION: ${LLVM_VERSION}")
# Check if LLVM was found and set variables
if(LLVM_FOUND)
  message(STATUS "LLVM found successfully.")
  # Ensure these values are not empty
if(NOT LLVM_INCLUDE_DIRS OR NOT LLVM_DEFINITIONS)
message(FATAL_ERROR "LLVM include directories or definitions are missing.")
endif() 
  # Set include directories and definitions
  include_directories(${LLVM_INCLUDE_DIRS})
  add_definitions(${LLVM_DEFINITIONS})
else()
  message(FATAL_ERROR "LLVM not found!")
endif()

# Check if the system is Linux
if(UNIX AND NOT APPLE)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/linux/lib/ DESTINATION "/usr/local/lib/FlowWing")
endif()

# use ccache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Using ccache, found in ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()



# Conditionally define TEST_MODE macro based on the build type (`cmake -DTESTS_ENABLED=ON ..`)
if(TESTS_ENABLED)
    # Locate GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    file(GLOB_RECURSE SOURCES ../../src/**.cpp ../../tests/**.cpp)
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/builtins/main.cpp")
    add_compile_definitions(AOT_TEST_MODE)
else()
    file(GLOB_RECURSE SOURCES ../../src/**.cpp)   
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/builtins/main.cpp")
    add_compile_definitions(AOT_MODE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_definitions(RELEASE)
endif()

# Compiler flags for optimization and debugging
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")  # Apply -O3 optimization for release builds
endif()

# Set the default executable name
set(DEFAULT_EXECUTABLE_NAME "FlowWing")

# Set the executable name based on whether it's a test build or not
if(TESTS_ENABLED)
    set(EXECUTABLE_NAME "FlowWing")
else()
    set(EXECUTABLE_NAME "FlowWing")
endif()


# Link the executable with the adjusted name
add_executable(${EXECUTABLE_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/../../src/compiler/AOTCompiler/AOTCompiler.cpp" ${SOURCES})

# Link LLVM libraries statically
llvm_map_components_to_libnames(LLVM_STATIC_LIBRARIES core executionengine orcjit native)

# Set libraries based on whether tests are enabled
set(LINK_LIBRARIES pthread ${LLVM_STATIC_LIBRARIES} LLVMInterpreter LLVMMCJIT ZLIB::ZLIB zstd::libzstd_shared LLVMTarget LLVMAnalysis LLVMAArch64Info)

if(TESTS_ENABLED)
    list(APPEND LINK_LIBRARIES ${GTEST_LIBRARIES})
endif()

# Link the executable with LLVM libraries and other dependencies
target_link_libraries(${EXECUTABLE_NAME} ${LINK_LIBRARIES})

# Set the output name of the executable
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${DEFAULT_EXECUTABLE_NAME})

# Link the version target to the build process
add_dependencies(FlowWing version)
# Creating Install Targets
if(NOT DEFINED CPACK_INSTALL_PREFIX)
  set(CPACK_INSTALL_PREFIX "/usr/local" CACHE STRING "Install prefix")
endif()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION  bin)
install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/FlowWing/ DESTINATION ${CPACK_INSTALL_PREFIX}/lib/FlowWing)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Set the output directory for the generated package
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/release")
set(CPACK_PACKAGE_CONTACT "Kushagra Rathore kushagrarathore002@gmail.com")
set(CPACK_PACKAGE_NAME "FlowWing")
set(CPACK_PACKAGE_VENDOR "Kushagra Rathore")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "FlowWing is a programming language that is designed to be fast, simple, and easy to use.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE.txt")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_EXECUTABLES "FlowWing" "FlowWing")

include(CPack)