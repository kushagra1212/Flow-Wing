cmake_minimum_required(VERSION 3.22.1)
project(FlowWing VERSION 0.0.1 LANGUAGES C CXX)

# =============================================================================
# 1. Project-Wide Settings
# =============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0075 NEW) # Allows for variable in list(REMOVE_ITEM)


if(APPLE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum macOS version")
endif()

# Use ccache for faster recompilation if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  message(STATUS "Using ccache, found in: ${CCACHE_FOUND}")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

# =============================================================================
# 2. Find Dependencies
# =============================================================================

find_package(LLVM 17 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_VERSION} for static linking.")

find_package(Threads REQUIRED)

# Option for enabling test builds, matching AOT structure
option(TESTS_ENABLED "Build with tests enabled" OFF)
if(TESTS_ENABLED)
  find_package(GTest REQUIRED)
endif()

# =============================================================================
# 3. Define Sources and Executable Target
# =============================================================================

# Add a custom target for version information, specific to JIT build
add_custom_target(version
    COMMAND ${CMAKE_COMMAND} -DVERSION=${PROJECT_VERSION} -P ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake
    COMMENT "Generating version information"
)

set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src)
file(GLOB_RECURSE ALL_PROJECT_SOURCES "${MAIN_SRC_DIR}/**.cpp")

# Exclude the main for the other build mode
list(REMOVE_ITEM ALL_PROJECT_SOURCES "${MAIN_SRC_DIR}/builtins/main.cpp")

set(EXECUTABLE_SOURCES ${ALL_PROJECT_SOURCES})

if(TESTS_ENABLED)
  set(MAIN_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../tests)
  file(GLOB_RECURSE TEST_SOURCES "${MAIN_TESTS_DIR}/**.cpp")
  list(APPEND EXECUTABLE_SOURCES ${TEST_SOURCES})
  set(EXECUTABLE_NAME "runTests")
else()
  set(EXECUTABLE_NAME "FlowWing")
endif()

add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})

# Ensure the final output binary is always named "FlowWing"
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "FlowWing")

# Make the version target a dependency for non-test builds
if(NOT TESTS_ENABLED)
  add_dependencies(${EXECUTABLE_NAME} version)
endif()


# =============================================================================
# 4. Configure Target-Specific Properties
# =============================================================================

# --- Include Directories ---
target_include_directories(${EXECUTABLE_NAME} PRIVATE
  ${LLVM_INCLUDE_DIRS}
)

# --- Compile Definitions ---
if(TESTS_ENABLED)
  target_compile_definitions(${EXECUTABLE_NAME} PRIVATE JIT_TEST_MODE)
else()
  target_compile_definitions(${EXECUTABLE_NAME} PRIVATE JIT_MODE)
endif()

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>:RELEASE>
  ${LLVM_DEFINITIONS}
)

# --- Compile Options / Flags ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE
  $<$<CONFIG:Debug>:-g -fsanitize=undefined>
  $<$<CONFIG:Release>:-O3>
)

# --- Linker Flags ---
target_link_options(${EXECUTABLE_NAME} PRIVATE
  $<$<CONFIG:Debug>:-fsanitize=undefined>
)

# --- Link Libraries ---
llvm_map_components_to_libnames(LLVM_STATIC_LIBRARIES
    core
    executionengine
    orcjit
    native
    interpreter
    mcjit
    target
    analysis
    aarch64info
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  ${LLVM_STATIC_LIBRARIES}
  Threads::Threads
)

if(TESTS_ENABLED)
  target_include_directories(${EXECUTABLE_NAME} PRIVATE ${GTest_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gtest_main)
endif()

# =============================================================================
# 5. Installation and Packaging
# =============================================================================

# Install the final binary to 'bin' and provided libs to 'lib'
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

if(UNIX AND NOT APPLE)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/linux-x86_64/lib/
            DESTINATION lib/FlowWing)
endif()


# --- CPack Configuration ---
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Kushagra Rathore")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, simple, and easy to use programming language.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE.txt")
set(CPACK_PACKAGE_EXECUTABLES "FlowWing" "FlowWing")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/release")

include(CPack)