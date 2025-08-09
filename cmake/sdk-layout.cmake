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
# FlowWing | SDK Layout Definition
#
# This script defines the layout and components of the FlowWing SDK.
# It sets variables that list the targets, files, and directories
# that should be installed or packaged for deployment.
# This keeps the logic separate from the installation commands themselves.
# =============================================================================

# - Define the custom library targets to be installed ---
set(SDK_LIBRARY_TARGETS
    built_in_module
    flowwing_string

    # Add other custom library target names here as you create them
    CACHE INTERNAL "List of custom library targets to include in the SDK."
)
message(STATUS "Found ${SDK_LIBRARY_TARGETS} custom libraries for SDK.")

# --Find all .fg module files to be installed ---
file(GLOB_RECURSE FG_MODULE_FILES "${CMAKE_SOURCE_DIR}/fw-modules/*.fg")
message(STATUS "Found .fg module files for SDK.")

# --Find all required third-party dependencies ---
set(DEPS_LIB_DIR "${CMAKE_SOURCE_DIR}/.fw_dependencies/install/lib")

# --Find all required third-party dependencies ---
file(GLOB THIRD_PARTY_LIBS
    "${DEPS_LIB_DIR}/libgc.a"
    "${DEPS_LIB_DIR}/libgccpp.a"
    "${DEPS_LIB_DIR}/libatomic_ops.a"

    # This glob will also find any other .a files you might need.
)
message(STATUS "Found third-party dependency libraries for SDK.")