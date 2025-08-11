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
# Strict Compiler Warnings
#
# Enforces a high level of compiler warnings to improve code quality and
# catch potential errors early. Warnings are treated as errors.
# =============================================================================

if(MSVC)
    # /W4 is a high warning level, /WX treats warnings as errors
    set(PROJECT_WARNING_FLAGS "/W4" "/WX")
else()
    # -Wall, -Wextra, -Wpedantic provide a comprehensive set of warnings
    # -Werror treats all warnings as errors
    set(PROJECT_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)
endif()

message(STATUS "Strict compiler warnings enabled: ${PROJECT_WARNING_FLAGS}")