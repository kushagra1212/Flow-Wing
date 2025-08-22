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
# Dependency Management (Refactored)
#
# This file finds pre-built dependencies that were installed by the
# external 'build_deps.cmake' script. It does NOT build them.
# =============================================================================

# Tell find_package() where to look for our pre-built libraries.
# This is the most important line.
set(DEPS_INSTALL_DIR ${CMAKE_SOURCE_DIR}/.fw_dependencies/install)
set(DEPS_INCLUDE_DIR ${DEPS_INSTALL_DIR}/include)
list(APPEND CMAKE_PREFIX_PATH ${DEPS_INSTALL_DIR})

set(CMAKE_FIND_ROOT_PATH ${DEPS_INSTALL_DIR})
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# --- LLVM ---

find_package(LLVM 17 REQUIRED CONFIG)
message(STATUS "Found pre-built LLVM ${LLVM_VERSION} at ${LLVM_DIR}")

# --- GTest (Conditional) ---
if(TESTS_ENABLED)
    find_package(GTest REQUIRED CONFIG)
    message(STATUS "Found pre-built GTest at ${GTest_DIR}")
endif()

# --- System Dependencies ---
find_package(Threads REQUIRED)
message(STATUS "Found Threads for threading support.")

if(APPLE)
    # Find the macOS SDK path to pass to our custom clang
    execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE MACOS_SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(NOT MACOS_SDK_PATH)
        message(FATAL_ERROR "Could not determine macOS SDK path using 'xcrun'. Make sure Xcode command line tools are installed.")
    endif()

    message(STATUS "Found macOS SDK for linker at: ${MACOS_SDK_PATH}")

    # This will be passed to C++ code
    set(MACOS_SDK_SYSROOT_FLAG "-isysroot ${MACOS_SDK_PATH}" CACHE INTERNAL "")
endif()

if(BUILD_AOT) # Use the clang from our local LLVM installation
    # Prefer clang++ for C++ linking, but fallback to clang

    if(MSVC)
    # On Windows with the Visual Studio toolchain, the linker is link.exe.
        set(AOT_LINKER_PATH "link.exe" CACHE FILEPATH "Path to the MSVC linker")
    else()
        # For other toolchains like GCC/Clang on Linux/macOS, the C++ compiler is also used as the linker driver.
        set(AOT_LINKER_PATH "${CXX_COMPILER}" CACHE FILEPATH "Path to clang/clang++ compiler")
    endif()

    message(STATUS "AOT linker for user code: ${AOT_LINKER_PATH}")
endif()