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

# --- Prerequisite Instructions ---
#
# macOS: brew install automake autoconf libtool
# Linux (Ubuntu/Debian): sudo apt-get install automake autoconf libtool
# Windows (Visual Studio): No prerequisites needed.
#
# --- End Prerequisite Instructions ---
if(UNIX)
    find_program(LIBTOOLIZE_EXECUTABLE NAMES glibtoolize libtoolize REQUIRED)
    find_program(AUTOCONF_EXECUTABLE autoconf REQUIRED)
    find_program(AUTOMAKE_EXECUTABLE automake REQUIRED)
    message(STATUS "Found Autotools for UNIX build.")
endif()

set(LLVM_ASSERTIONS_SETTING OFF)
set(CMAKE_CONFIG_TYPE ${CMAKE_BUILD_TYPE})

# --- Environment flags for Autotools ---
set(AUTOTOOLS_ENV_ARGS)

if(UNIX)
    set(ENV_C_FLAGS "")
    set(ENV_CXX_FLAGS "")

    if(APPLE)
        execute_process(COMMAND xcrun --show-sdk-path OUTPUT_VARIABLE MACOSX_SDK_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)

        if(EXISTS "${MACOSX_SDK_PATH}")
            message(STATUS "Found macOS SDK. Will pass it to compiler: ${MACOSX_SDK_PATH}")
            set(ENV_C_FLAGS "${ENV_C_FLAGS} -isysroot ${MACOSX_SDK_PATH}")
            set(ENV_CXX_FLAGS "${ENV_CXX_FLAGS} -isysroot ${MACOSX_SDK_PATH}")
        endif()
    endif()

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(LLVM_ASSERTIONS_SETTING ON)
        set(ENV_C_FLAGS "${ENV_C_FLAGS} -g -O0")
        set(ENV_CXX_FLAGS "${ENV_CXX_FLAGS} -g -O0")
        message(STATUS "Configuring for a Debug build: LLVM Assertions ON, Autotools debug flags ON.")
    else()
        set(CMAKE_CONFIG_TYPE "Release") # Default to Release
        message(STATUS "Configuring for a Release build: LLVM Assertions OFF.")
    endif()

    # Build the list of environment variables correctly for the 'env' command
    list(APPEND AUTOTOOLS_ENV_ARGS "CFLAGS=${ENV_C_FLAGS}" "CXXFLAGS=${ENV_CXX_FLAGS}")
endif()

set(DEPS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/../install")
message("DEPS_INSTALL_DIR: ${DEPS_INSTALL_DIR}")

set(STAMP_FILE "${CMAKE_CURRENT_BINARY_DIR}/../stamps/.installed-${CMAKE_BUILD_TYPE}")
message("STAMP FILE: ${STAMP_FILE}")

if(EXISTS "${STAMP_FILE}")
    message(STATUS "Dependencies already built in ${DEPS_INSTALL_DIR}")
else()
    set(GC_DEPENDENCY "")

    if(UNIX)
        ExternalProject_Add(
            libatomic_ops_external
            GIT_REPOSITORY "https://github.com/ivmai/libatomic_ops.git"
            GIT_TAG "v7.8.0"
            UPDATE_COMMAND ""
            BUILD_IN_SOURCE 1
            CONFIGURE_COMMAND ./autogen.sh && env ${AUTOTOOLS_ENV_ARGS} ./configure --prefix=${DEPS_INSTALL_DIR} --enable-static --disable-shared
            BUILD_COMMAND make
            INSTALL_COMMAND make install
            USES_TERMINAL_DOWNLOAD true
            USES_TERMINAL_CONFIGURE true
            USES_TERMINAL_BUILD true
            USES_TERMINal_INSTALL true
        )

        # FIX: Append the library/include path flags to the list for bdw-gc
        set(BDWGC_ENV_ARGS ${AUTOTOOLS_ENV_ARGS})
        list(APPEND BDWGC_ENV_ARGS "CPPFLAGS=-I${DEPS_INSTALL_DIR}/include" "LDFLAGS=-L${DEPS_INSTALL_DIR}/lib")

        ExternalProject_Add(
            bdwgc_external
            DEPENDS libatomic_ops_external
            GIT_REPOSITORY "https://github.com/ivmai/bdwgc.git"
            GIT_TAG "v8.2.4"
            UPDATE_COMMAND ""
            BUILD_IN_SOURCE 1
            CONFIGURE_COMMAND ./autogen.sh && env ${BDWGC_ENV_ARGS} ./configure --prefix=${DEPS_INSTALL_DIR} --enable-static --disable-shared --enable-cplusplus
            BUILD_COMMAND make
            INSTALL_COMMAND make install
            USES_TERMINAL_DOWNLOAD true
            USES_TERMINAL_CONFIGURE true
            USES_TERMINAL_BUILD true
            USES_TERMINAL_INSTALL true
        )
        set(GC_DEPENDENCY "bdwgc_external")

    elseif(WIN32)
        # (Windows section remains unchanged)
        ExternalProject_Add(
            bdwgc_external
            GIT_REPOSITORY "https://github.com/ivmai/bdwgc.git"
            GIT_TAG "v8.2.4"

            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE} -Dbuild_tests=OFF -Dbuild_gctests=OFF -Denable_cplusplus=ON -DBUILD_SHARED_LIBS=OFF
            USES_TERMINAL_DOWNLOAD true
            USES_TERMINAL_CONFIGURE true
            USES_TERMINAL_BUILD true
            USES_TERMINAL_INSTALL true
        )
        set(GC_DEPENDENCY "bdwgc_external")
    endif()

    # (LLVM and GTest sections remain unchanged)
    ExternalProject_Add(
        llvm_external
        DEPENDS ${GC_DEPENDENCY}

        # --- REPLACED a URL download with a Git Clone ---
        GIT_REPOSITORY "https://github.com/llvm/llvm-project.git"
        GIT_TAG "llvmorg-17.0.6" # The official tag for version 17.0.6
        GIT_SHALLOW TRUE # Downloads only the history for that one tag

        # --- END REPLACEMENT ---
        SOURCE_SUBDIR llvm

        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE} -DLLVM_ENABLE_PROJECTS=clang;lld -DLLVM_TARGETS_TO_BUILD=Native -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_ENABLE_ASSERTIONS=${LLVM_ASSERTIONS_SETTING} -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_EH=ON -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_EXAMPLES=OFF -DLLVM_INCLUDE_BENCHMARKS=OFF -DLLVM_BUILD_LLVM_DYLIB=ON -DLLVM_LINK_LLVM_DYLIB=ON
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
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