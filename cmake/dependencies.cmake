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
# Dependency Management
#
# Finds and configures all external dependencies required by the project,
# such as LLVM, Threads, and GTest.
# =============================================================================

# --- LLVM ---
find_package(LLVM 17 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_VERSION} for static linking.")

# --- Threads ---
find_package(Threads REQUIRED)
message(STATUS "Found Threads for threading support.")

# --- AOT Linker (Conditional) ---
if(BUILD_AOT)
    find_program(AOT_LINKER_PATH
        NAMES clang-17 clang++ clang
        REQUIRED
        DOC "Path to the clang compiler for AOT linking.")
    message(STATUS "AOT linker for user code: ${AOT_LINKER_PATH}")
endif()

# --- GTest (Conditional) ---
if(TESTS_ENABLED)
    find_package(GTest REQUIRED)
endif()