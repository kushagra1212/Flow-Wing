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

    "MACOS_SDK_SYSROOT_FLAG=\"${MACOS_SDK_SYSROOT_FLAG}\""

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
    $<$<CONFIG:Release>:-O3>
    -frtti)

# --- Linker Options / Flags ---
target_link_options(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=undefined>)