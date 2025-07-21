cmake_minimum_required(VERSION 3.22)
project(FlowWing VERSION 0.0.2 LANGUAGES C CXX)

# =============================================================================
# 1. Project-Wide Settings & Deployment Targets
# =============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CRITICAL FOR MACOS DEPLOYMENT: Set the minimum macOS version for compatibility.
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

# Option for enabling test builds
option(TESTS_ENABLED "Build with tests enabled" OFF)
if(TESTS_ENABLED)
  find_package(GTest REQUIRED)
endif()


# Add a custom target for version information, specific to APT build
add_custom_target(version
    COMMAND ${CMAKE_COMMAND} -DVERSION=${PROJECT_VERSION} -P ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake
    COMMENT "Generating version information"
)
# =============================================================================
# 3. Define Sources and Executable Target
# =============================================================================

set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src)
file(GLOB_RECURSE ALL_PROJECT_SOURCES "${MAIN_SRC_DIR}/**.cpp")

# Remove the other main.cpp if it exists
list(REMOVE_ITEM ALL_PROJECT_SOURCES "${MAIN_SRC_DIR}/builtins/main.cpp")

set(EXECUTABLE_SOURCES ${ALL_PROJECT_SOURCES})

if(TESTS_ENABLED)
  set(MAIN_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../tests)
  file(GLOB_RECURSE TEST_SOURCES "${MAIN_TESTS_DIR}/**.cpp")
  list(APPEND EXECUTABLE_SOURCES ${TEST_SOURCES})
endif()

# Define the executable target. This will be a single, large binary.
add_executable(FlowWing ${EXECUTABLE_SOURCES})

# =============================================================================
# 4. Configure Target-Specific Properties
# =============================================================================

# --- Include Directories ---
target_include_directories(FlowWing PRIVATE
  ${LLVM_INCLUDE_DIRS}
)

# --- Compile Definitions ---
if(TESTS_ENABLED)
  target_compile_definitions(FlowWing PRIVATE AOT_TEST_MODE)
else()
  target_compile_definitions(FlowWing PRIVATE AOT_MODE)
endif()

target_compile_definitions(FlowWing PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>:RELEASE>
  ${LLVM_DEFINITIONS}
)

# --- Compile Options / Flags ---

target_compile_options(FlowWing PRIVATE
  $<$<CONFIG:Debug>:-g -fsanitize=undefined>
  $<$<CONFIG:Release>:-O3>
)


# --- Linker Options / Flags (NOT USING DUE TO ISSUES)
# We also need to pass the sanitize flag to the linker so it includes
# the required sanitizer runtime libraries.
target_link_options(FlowWing PRIVATE
  $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

# --- Link Libraries ---

# Use a different strategy for Debug vs. Release


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

target_link_libraries(FlowWing PRIVATE
  ${LLVM_STATIC_LIBRARIES}
  Threads::Threads
)

if(TESTS_ENABLED)
  target_include_directories(FlowWing PRIVATE ${GTest_INCLUDE_DIRS})
  target_link_libraries(FlowWing PRIVATE GTest::gtest_main)
endif()

# =============================================================================
# 5. Installation and Packaging (Static Linking Method)
# =============================================================================

# Install the final, self-contained binary to the 'bin' directory.
install(TARGETS FlowWing DESTINATION bin)

# --- CPack Configuration for a simple DMG ---
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Kushagra Rathore")
set(CPACK_PACKAGE_CONTACT "kushagrarathore002@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, simple, and easy to use programming language.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE.txt")
set(CPACK_PACKAGE_EXECUTABLES "FlowWing" "FlowWing")

# Use the "DragNDrop" generator on macOS to create a user-friendly DMG
if(APPLE)
  set(CPACK_GENERATOR "DragNDrop")
endif()

include(CPack)