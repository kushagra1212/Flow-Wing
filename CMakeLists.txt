# =============================================================================
# FlowWing | CMake Main Entry Point
#
# This file serves as the primary entry point for the CMake build system.
# It defines the project and orchestrates the inclusion of modular scripts
# from the '/cmake' directory to configure the build process.
# =============================================================================

cmake_minimum_required(VERSION 3.22)
project(FlowWing VERSION 0.0.2 LANGUAGES C CXX)

# Include modular CMake scripts to configure the build.
# The order of inclusion is critical.
include(cmake/project-settings.cmake)
include(cmake/compiler-warnings.cmake)
include(cmake/dependencies.cmake)
include(cmake/targets.cmake)
include(cmake/installation.cmake)
include(cmake/packaging.cmake)

# Conditional inclusion of testing configuration.
if(TESTS_ENABLED)
    include(cmake/testing.cmake)
endif()