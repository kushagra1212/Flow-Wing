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
# FlowWing | Installation Rules
# =============================================================================

# Get the list of all components that constitute our SDK.
include(cmake/sdk-layout.cmake)

# --Install the main compiler executable.
# The EXECUTABLE_NAME is set in targets.cmake (e.g., "FlowWing" or "runTests").
install(TARGETS ${EXECUTABLE_NAME}
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION . # Correctly handles macOS .app bundles
)

# --Install the custom-built C/C++ libraries from fw-modules.
install(TARGETS ${SDK_LIBRARY_TARGETS}
    ARCHIVE DESTINATION ${FLOWWING_PLATFORM_LIB_DIR}
    LIBRARY DESTINATION ${FLOWWING_PLATFORM_LIB_DIR}
)

# --Install the .fg module source files from fw-modules.
install(FILES ${FG_MODULE_FILES}
    DESTINATION lib/modules
)

# --Install the required third-party dependencies from .fw_dependencies.
install(FILES ${THIRD_PARTY_LIBS}
    DESTINATION ${FLOWWING_PLATFORM_LIB_DIR}
)

message(STATUS "Installation rules configured for the FlowWing SDK.")