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
# FlowWing | CMake Main Entry Point
#
# This file serves as the primary entry point for the CMake build system.
# It defines the project and orchestrates the inclusion of modular scripts
# from the '/cmake' directory to configure the build process.
# =============================================================================
cmake_minimum_required(VERSION 3.29)
project(FlowWing VERSION 0.0.2 LANGUAGES C CXX)

# Include modular CMake scripts to configure the build.
# The order of inclusion is critical.
include(cmake/project-settings.cmake)
include(cmake/compiler-warnings.cmake)
include(cmake/dependencies.cmake)

# Add the module sources to the build. This will define the library
# targets like 'flowwing_string' and 'flowwing_map'.
add_subdirectory(fw-modules)

include(cmake/targets.cmake)
include(cmake/installation.cmake)
include(cmake/packaging.cmake)

# Conditional inclusion of testing configuration.
if(TESTS_ENABLED)
    include(cmake/testing.cmake)
endif()