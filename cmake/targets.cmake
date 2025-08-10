#
# FlowWing Compiler
# Copyright (C) 2023-2025 Kushagra Rathore
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

# =============================================================================
# Target Definitions
#
# Defines all build targets, including the main executable and custom targets.
# This file configures sources, include paths, libraries, and compiler
# definitions for each target.
# =============================================================================

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

# --- 1. Define the platform-specific library directory ---
# Creates a path like 'lib/Darwin-arm64' or 'lib/Linux-x86_64'.
set(FLOWWING_PLATFORM_LIB_DIR "lib/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}"
    CACHE STRING "Platform-specific directory for FlowWing libraries.")
message(STATUS "SDK Platform Library Path: ${FLOWWING_PLATFORM_LIB_DIR}")

set(FLOWWING_MODULES_DIR "lib/modules"
    CACHE STRING "Platform-specific directory for FlowWing modules.")
message(STATUS "SDK Modules Path: ${FLOWWING_MODULES_DIR}")

# --- Executable Target Definition ---
add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})

add_dependencies(${EXECUTABLE_NAME} version)

# =============================================================================
# Target-Specific Properties
# =============================================================================
message(STATUS "[LLVM_INCLUDE_DIRS]: ${LLVM_INCLUDE_DIRS}")

# --- Include Directories ---
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}

    # Add LLVM and Clang headers explicitly for the FetchContent build
    ${LLVM_INCLUDE_DIRS}
)

# --- Link Libraries ---
target_link_libraries(${EXECUTABLE_NAME} PRIVATE

    # JIT and Execution Components
    LLVMOrcJIT
    LLVMExecutionEngine
    LLVMJITLink
    LLVMRuntimeDyld
    LLVMMCJIT
    LLVMInterpreter

    # Code Generation and Optimization
    LLVMCodeGen
    LLVMTarget
    LLVMTransformUtils
    LLVMAnalysis
    LLVMipo
    LLVMObject

    # Core LLVM Components
    LLVMCore
    LLVMMC
    LLVMSupport
    LLVMBinaryFormat
    LLVMDemangle

    # System Libraries
    Threads::Threads)

# --- Conditionally Link Target-Specific Backends ---
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    message(STATUS "Linking against X86 backend.")
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        LLVMX86CodeGen
        LLVMX86AsmParser
        LLVMX86Desc
        LLVMX86Info
    )
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    message(STATUS "Linking against AArch64 backend.")
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        LLVMAArch64CodeGen
        LLVMAArch64AsmParser
        LLVMAArch64Desc
        LLVMAArch64Info
    )
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}. Please add linking logic for this target.")
endif()

if(TESTS_ENABLED)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${googletest_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gtest)
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

if(NOT BUILD_AOT)
    message(STATUS "JIT build detected. Forcing link of static JIT dependencies.")

    # Get the path from your dependencies.cmake file
    set(DEPS_LIB_DIR "${CMAKE_SOURCE_DIR}/.fw_dependencies/install/lib")

    if(APPLE)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE
            "-Wl,-all_load"
            "-Wl,-force_load,$<TARGET_FILE:built_in_module>"
            "-Wl,-force_load,${DEPS_LIB_DIR}/libgc.a"
            "-Wl,-force_load,${DEPS_LIB_DIR}/libgccpp.a"
            "-Wl,-force_load,${DEPS_LIB_DIR}/libatomic_ops.a"
        )
    elseif(UNIX)
        # This is the corrected section for Linux
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE
            "-Wl,--whole-archive"
            built_in_module
            "${DEPS_LIB_DIR}/libgc.a"
            "${DEPS_LIB_DIR}/libgccpp.a"
            "${DEPS_LIB_DIR}/libatomic_ops.a"
            "-Wl,--no-whole-archive"

            # This flag forces all global symbols to be added to the dynamic symbol table,
            # which is necessary for the JIT to find them at runtime.
            "-Wl,--export-dynamic"
        )
    endif()
endif()

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    ${LLVM_DEFINITIONS}

    "MACOS_SDK_SYSROOT_FLAG=\"${MACOS_SDK_SYSROOT_FLAG}\""
    "FLOWWING_PLATFORM_LIB_DIR=\"${FLOWWING_PLATFORM_LIB_DIR}\""
    "AOT_LINKER_PATH=\"${AOT_LINKER_PATH}\""
    "PROJECT_DIR=\"${CMAKE_SOURCE_DIR}\""
)

if(TESTS_ENABLED)
    # Define the SDK path relative to the project root. This must match the Makefile.
    set(TEST_SDK_PATH "${CMAKE_SOURCE_DIR}/build/test-sdk")

    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE
        "TEST_SDK_PATH=\"${TEST_SDK_PATH}\""
    )
endif()

# --- Compile Options / Flags ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE
    ${PROJECT_WARNING_FLAGS}
    $<$<CONFIG:Debug>:-g -fsanitize=undefined>
    $<$<CONFIG:Release>:-O3>
    -frtti)

# --- Linker Options / Flags ---
target_link_options(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=undefined>)