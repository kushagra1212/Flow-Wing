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

cmake_minimum_required(VERSION 3.29)
project(DependencySuperbuild NONE)

include(ExternalProject)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LLVM_ASSERTIONS_SETTING ON)
    message(STATUS "Configuring for a Debug build: LLVM Assertions will be ON.")
else()
    set(LLVM_ASSERTIONS_SETTING OFF)
    message(STATUS "Configuring for a Release build: LLVM Assertions will be OFF.")
endif()

set(DEPS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/../install")

# Check if we already have dependencies
if(EXISTS "${DEPS_INSTALL_DIR}/lib/cmake/llvm/LLVMConfig.cmake" AND
    EXISTS "${DEPS_INSTALL_DIR}/lib/cmake/GTest/GTestConfig.cmake")
    message(STATUS "Dependencies already built in ${DEPS_INSTALL_DIR}")
    install(CODE "file(TOUCH \"${DEPS_INSTALL_DIR}/.installed\")")
else()
    ExternalProject_Add(
        llvm_external
        URL
        "https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/llvm-project-17.0.6.src.tar.xz"
        URL_HASH
        "SHA256=58a8818c60e6627064f312dbf46c02d9949956558340938b71cf731ad8bc0813"

        # ---- FIX #1: Specify the subdirectory containing the main CMakeLists.txt ----
        SOURCE_SUBDIR llvm

        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=Release

        # ---- FIX #2: Use semicolons to separate list items for CMake ----
        -DLLVM_ENABLE_PROJECTS=clang;lld

        -DLLVM_TARGETS_TO_BUILD=AArch64
        -DLLVM_ENABLE_TERMINFO=OFF
        -DLLVM_ENABLE_ASSERTIONS=${LLVM_ASSERTIONS_SETTING}
        -DLLVM_ENABLE_RTTI=ON
        -DLLVM_ENABLE_EH=ON
        -DLLVM_INCLUDE_TESTS=OFF
        -DLLVM_INCLUDE_EXAMPLES=OFF
        -DLLVM_INCLUDE_BENCHMARKS=OFF
        -DLLVM_BUILD_LLVM_DYLIB=ON
        -DLLVM_LINK_LLVM_DYLIB=ON

        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_UPDATE true
        USES_TERMINAL_PATCH true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
        USES_TERMINAL_TEST true
    )

    # --- GTest External Project ---
    ExternalProject_Add(
        gtest_external

        # FIX #2: Add DEPENDS to control build order
        DEPENDS llvm_external

        URL "https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz"
        URL_HASH "SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c"

        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=Release
        -DBUILD_GMOCK=OFF
        -DCMAKE_POLICY_DEFAULT_CMP0068=NEW

        # Add USES_TERMINAL flags to see the output
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
    )

    install(CODE "file(TOUCH \"${DEPS_INSTALL_DIR}/.installed\")")
endif()