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
# Project-Wide Settings & Build Mode
#
# Configures core project settings, build options (like AOT, tests),
# and initializes tools like ccache.
# =============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_policy(SET CMP0075 NEW) # Allows for variable in list(REMOVE_ITEM)

# C and CXX compilers being used for this configuration.
set(C_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/.fw_dependencies/install/bin/clang")
set(CXX_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/.fw_dependencies/install/bin/clang++")
message(STATUS "C compiler: ${C_COMPILER}")
message(STATUS "C++ compiler: ${CXX_COMPILER}")

# CRITICAL FOR MACOS DEPLOYMENT: Set the minimum macOS version.
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum macOS version")
endif()

# --- Build Mode Selection ---
option(BUILD_AOT "Enable Ahead-of-Time (AOT) compilation mode." OFF)
option(TESTS_ENABLED "Build with tests enabled" OFF)
option(DEV_MODE "Enable developer mode (Build with hard-coded developer paths)" OFF)

# --- Find and configure ccache for faster recompilation ---
find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
    message(STATUS "Using ccache, found in: ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()