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
# Installation Rules
#
# Defines the rules for installing project artifacts, such as the main
# executable, language modules, and shared libraries.
# =============================================================================

# Install the final binary
if(IS_MACOS_BUNDLE)
    install(TARGETS ${EXECUTABLE_NAME} BUNDLE DESTINATION .)
else()
    install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
endif()

# Install the language modules (.fg files)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DEV_MODULES_PATH}/
    DESTINATION ${INSTALL_MODULES_DEST}
)

# Install the shared libraries (.so, .a, .dll, etc.)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DEV_LIBS_PATH}/
    DESTINATION ${INSTALL_LIBS_DEST}
    FILES_MATCHING
    PATTERN "*.so*"
    PATTERN "*.a"
    PATTERN "*.dylib"
    PATTERN "*.dll"
    PATTERN "*.bc"
)