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
# CPack Packaging Configuration
#
# Configures CPack for creating distributable packages for different
# operating systems (e.g., DEB for Linux, DragNDrop for macOS, NSIS for Windows).
# =============================================================================

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Kushagra Rathore")
set(CPACK_PACKAGE_CONTACT "kushagrarathore002@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, simple, and easy to use programming language.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_EXECUTABLES "FlowWing" "FlowWing")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/release")

# --- Platform-Specific CPack Generators ---
if(WIN32)
    set(CPACK_GENERATOR "NSIS")

# Add NSIS-specific customizations here if needed
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB")
endif()

include(CPack)