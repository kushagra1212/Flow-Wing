# =============================================================================
# Target Definitions
#
# Defines all build targets, including the main executable and custom targets.
# This file configures sources, include paths, libraries, and compiler
# definitions for each target.
# =============================================================================

# --- Path and Platform Configuration ---
if(APPLE)
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
        set(PLATFORM_SUBDIR "mac-silicon")
    else()
        set(PLATFORM_SUBDIR "mac-intel")
    endif()
elseif(UNIX)
    set(PLATFORM_SUBDIR "linux-x86_64")
elseif(WIN32)
    set(PLATFORM_SUBDIR "windows-x64")
endif()

set(DEV_MODULES_PATH "lib/modules")
set(DEV_LIBS_PATH "lib/${PLATFORM_SUBDIR}")
message(STATUS "Found platform libraries to install at: ${DEV_LIBS_PATH}")

set(IS_MACOS_BUNDLE OFF)

if(APPLE AND NOT TESTS_ENABLED AND CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT DEV_MODE)
    set(IS_MACOS_BUNDLE ON)
endif()

if(IS_MACOS_BUNDLE)
    set(INSTALL_MODULES_DEST "Resources/modules")
    set(INSTALL_LIBS_DEST "Resources")
else()
    set(INSTALL_MODULES_DEST "share/flowwing/modules")
    set(INSTALL_LIBS_DEST "lib/flowwing")
endif()

# --- Custom Version Target ---
add_custom_target(version
    COMMAND ${CMAKE_COMMAND} -DVERSION=${PROJECT_VERSION} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake
    COMMENT "Generating version information")

# --- Source File Configuration ---
set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE EXECUTABLE_SOURCES "${MAIN_SRC_DIR}/**.cpp")

if(TESTS_ENABLED)
    set(MAIN_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    file(GLOB_RECURSE TEST_SOURCES "${MAIN_TESTS_DIR}/**.cpp")
    list(APPEND EXECUTABLE_SOURCES ${TEST_SOURCES})
    set(EXECUTABLE_NAME "runTests")
else()
    set(EXECUTABLE_NAME "FlowWing")
endif()

# --- Executable Target Definition ---
if(IS_MACOS_BUNDLE)
    add_executable(${EXECUTABLE_NAME} MACOSX_BUNDLE ${EXECUTABLE_SOURCES})
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        OUTPUT_NAME "FlowWing"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist)
else()
    add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})
endif()

add_dependencies(${EXECUTABLE_NAME} version)

# =============================================================================
# Target-Specific Properties
# =============================================================================

# --- Include Directories ---
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LLVM_INCLUDE_DIRS})

# --- Link Libraries ---
llvm_map_components_to_libnames(LLVM_STATIC_LIBRARIES
    core executionengine orcjit native interpreter mcjit
    target analysis aarch64info)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    ${LLVM_STATIC_LIBRARIES}
    Threads::Threads)

if(TESTS_ENABLED)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${GTest_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gtest_main)
endif()

# --- Compile Definitions ---
if(BUILD_AOT)
    # AOT Mode Definitions
    if(TESTS_ENABLED)
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE AOT_TEST_MODE)
    else()
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE AOT_MODE)
    endif()
else()
    # JIT Mode Definitions
    if(TESTS_ENABLED)
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE JIT_TEST_MODE)
    else()
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE JIT_MODE)
    endif()
endif()

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    ${LLVM_DEFINITIONS}
    "DEV_MODULES_PATH=\"${DEV_MODULES_PATH}\""
    "DEV_LIBS_PATH=\"${DEV_LIBS_PATH}\""
    "INSTALL_MODULES_PATH=\"${INSTALL_MODULES_DEST}\""
    "INSTALL_LIBS_PATH=\"${INSTALL_LIBS_DEST}\""
    "AOT_LINKER_PATH=\"${AOT_LINKER_PATH}\""
    "DEV_MODE_PATH=\"${CMAKE_SOURCE_DIR}\"")

# --- Compile Options / Flags ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE
    ${PROJECT_WARNING_FLAGS}
    $<$<CONFIG:Debug>:-g -fsanitize=undefined>
    $<$<CONFIG:Release>:-O3>)

# --- Linker Options / Flags ---
target_link_options(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=undefined>)