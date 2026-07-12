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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

cmake_minimum_required(VERSION 3.29)
project(DependencySuperbuild NONE)

include(ExternalProject)

set(LLVM_ASSERTIONS_SETTING OFF)
set(CMAKE_CONFIG_TYPE ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LLVM_ASSERTIONS_SETTING ON)
    message(STATUS "Configuring for a Debug build: LLVM Assertions ON.")
else()
    set(CMAKE_CONFIG_TYPE "Release") # Default to Release
    message(STATUS "Configuring for a Release build: LLVM Assertions OFF.")
endif()

set(DEPS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/../install")
message("DEPS_INSTALL_DIR: ${DEPS_INSTALL_DIR}")

set(STAMP_FILE "${CMAKE_CURRENT_BINARY_DIR}/../stamps/.installed-${CMAKE_BUILD_TYPE}")
message("STAMP FILE: ${STAMP_FILE}")

if(EXISTS "${STAMP_FILE}")
    message(STATUS "Dependencies already built in ${DEPS_INSTALL_DIR}")
else()
   ExternalProject_Add(
        raylib_external
        GIT_REPOSITORY  "https://github.com/raysan5/raylib.git"
        GIT_TAG "5.5"
        GIT_SHALLOW TRUE
        CMAKE_ARGS 
            -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE}
            -DBUILD_EXAMPLES=OFF
            -DBUILD_GAMES=OFF
            -DCUSTOMIZE_BUILD=ON
            -DBUILD_SHARED_LIBS=OFF
            -DPLATFORM=Desktop
        USES_TERMINAL_DOWNLOAD true 
        USES_TERMINAL_CONFIGURE true 
        USES_TERMINAL_BUILD true 
        USES_TERMINAL_INSTALL true
        GIT_PROGRESS TRUE
    )

    ExternalProject_Add(
        mongo_c_driver_external
        GIT_REPOSITORY  "https://github.com/mongodb/mongo-c-driver.git"
        GIT_TAG         "2.3.0"
        GIT_SHALLOW     TRUE
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE}
            -DBUILD_SHARED_LIBS=OFF
            -DENABLE_TESTS=OFF
            -DENABLE_EXAMPLES=OFF
            -DENABLE_SASL=OFF
            -DENABLE_SRV=OFF
            -DENABLE_SNAPPY=OFF
            -DENABLE_ZSTD=OFF
            -DENABLE_ZLIB=BUNDLED
            -DENABLE_MONGOC=ON
            -DENABLE_BSON=ON
            -DENABLE_STATIC=ON
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
        GIT_PROGRESS TRUE
    )

    set(LLVM_BUILD_SHARED OFF)

    if(NOT WIN32)
        set(LLVM_BUILD_SHARED ON)
    endif()

    # (LLVM and GTest sections remain unchanged)
    ExternalProject_Add(
        llvm_external

        # --- REPLACED a URL download with a Git Clone ---
        GIT_REPOSITORY "https://github.com/llvm/llvm-project.git"
        GIT_TAG "llvmorg-17.0.6" # The official tag for version 17.0.6
        GIT_SHALLOW TRUE # Downloads only the history for that one tag

        # --- END REPLACEMENT ---
        SOURCE_SUBDIR llvm

        # IMPORTANT: CMAKE_ARGS is itself a CMake list, so a literal `;` inside a single
        # argument (like -DLLVM_ENABLE_PROJECTS=clang;lld) is interpreted as an outer list
        # separator — the sub-CMake only sees -DLLVM_ENABLE_PROJECTS=clang and the stray
        # token `lld` gets silently dropped, so LLD is NEVER built (no lld-link.exe, no
        # ld.lld, no ld64.lld). Use LIST_SEPARATOR to pick a non-semicolon character for
        # the outer list and substitute it back to `;` when the nested CMake is invoked.
        # See https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add
        LIST_SEPARATOR "|"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE} -DLLVM_ENABLE_PROJECTS=clang|lld -DLLVM_TARGETS_TO_BUILD=Native -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_ENABLE_ASSERTIONS=${LLVM_ASSERTIONS_SETTING} -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_EH=ON -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_EXAMPLES=OFF -DLLVM_INCLUDE_BENCHMARKS=OFF -DLLVM_BUILD_LLVM_DYLIB=${LLVM_BUILD_SHARED} -DLLVM_LINK_LLVM_DYLIB=${LLVM_BUILD_SHARED}
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
        
        GIT_PROGRESS TRUE
    )

    ExternalProject_Add(
        gtest_external
        DEPENDS llvm_external
        URL "https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz"
        URL_HASH "SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE} -DBUILD_GMOCK=OFF

     
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
    )
endif()