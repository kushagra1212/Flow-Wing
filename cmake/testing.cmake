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
# CTest Testing Configuration
#
# Configures the testing framework (CTest) for the project. This file is
# only included when the 'TESTS_ENABLED' option is ON.
# =============================================================================

# Enable testing for this project. This must be called before add_test().
enable_testing()

# Register the test executable with CTest.
add_test(NAME FlowWing-GTest COMMAND ${EXECUTABLE_NAME} --gtest_color=yes)