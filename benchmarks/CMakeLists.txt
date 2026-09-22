#
# FlowWing Compiler
# Copyright (C) 2023-2026 Kushagra Rathore
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
# FlowWing | Benchmark Suite
#
# Standalone project. It is deliberately NOT included from the root
# CMakeLists.txt and it does NOT add anything to cmake/deps_builder.
#
# The reason is the CI cache key. cmake/deps_builder/deps.lock is hashed to
# decide whether LLVM and friends must be rebuilt on all three platforms, and
# that rebuild costs roughly three hours. Google Benchmark is a development
# tool for this suite alone, so it is fetched here instead. Adding a line to
# deps.lock for it would invalidate the compiler's dependency cache for
# everyone.
# =============================================================================
cmake_minimum_required(VERSION 3.29)

project(FlowWingBenchmarks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# The repository this suite measures. Baked in so the driver needs no
# arguments in the common case; override with --repo-root=<path>.
get_filename_component(FW_BENCH_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)

# --- Google Benchmark ---------------------------------------------------------
include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_INSTALL_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(googlebenchmark
    URL "https://github.com/google/benchmark/archive/refs/tags/v1.9.1.tar.gz"
    URL_HASH "SHA256=32131c08ee31eeff2c8968d7e874f3cb648034377dfc32a4c377fa8796d84981"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googlebenchmark)

# --- Driver -------------------------------------------------------------------
add_executable(bench_driver
    harness/bench_driver.cpp
    harness/bench_case.cpp
    harness/markdown_reporter.cpp
    harness/process.cpp
    harness/system_info.cpp
    harness/toolchain.cpp
)

target_include_directories(bench_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/harness)

target_compile_definitions(bench_driver PRIVATE
    FW_BENCH_REPO_ROOT="${FW_BENCH_REPO_ROOT}")

target_link_libraries(bench_driver PRIVATE benchmark::benchmark)

if(NOT UNIX)
    message(FATAL_ERROR
        "The benchmark driver spawns child processes with posix_spawn and is "
        "currently POSIX-only (macOS and Linux). Windows support means adding "
        "a CreateProcess path to harness/process.cpp.")
endif()
