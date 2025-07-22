cmake_minimum_required(VERSION 3.22)
project(FlowWing VERSION 0.0.2 LANGUAGES C CXX)

# =============================================================================
# 1. Project-Wide Settings & Build Mode
# =============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0075 NEW) # Allows for variable in list(REMOVE_ITEM)

# CRITICAL FOR MACOS DEPLOYMENT: Set the minimum macOS version for compatibility.
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum macOS version")
endif()

# --- BUILD MODE SELECTION ---
option(BUILD_AOT "Enable Ahead-of-Time (AOT) compilation mode." OFF)
option(TESTS_ENABLED "Build with tests enabled" OFF)
option(DEV_MODE "Enable developer mode (Build with hard-coded developer paths (for local running))" OFF)

# Use ccache for faster recompilation if available
find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
    message(STATUS "Using ccache, found in: ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

# =============================================================================
# 2. Find Dependencies
# =============================================================================
find_package(LLVM 17 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_VERSION} for static linking.")

find_package(Threads REQUIRED)
message(STATUS "Found Threads for threading support.")

if(BUILD_AOT)
    find_program(AOT_LINKER_PATH
        NAMES clang-17 clang++ clang
        REQUIRED # This makes CMake fail if it can't find any of them
        DOC "Path to the clang compiler that FlowWing will use to link user code.")

    message(STATUS "The FlowWing compiler will use this linker for AOT builds: ${AOT_LINKER_PATH}")
endif()

if(TESTS_ENABLED)
    find_package(GTest REQUIRED)
endif()

set(IS_MACOS_BUNDLE OFF)

if(APPLE AND NOT TESTS_ENABLED AND CMAKE_BUILD_TYPE STREQUAL "Release" AND NOT DEV_MODE)
    set(IS_MACOS_BUNDLE ON)
endif()

# This command tells CMake to generate the compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Dependencies & Tools
if(APPLE)
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
        set(PLATFORM_SUBDIR "mac-silicon")
    else()
        set(PLATFORM_SUBDIR "mac-intel")
    endif()
elseif(UNIX)
    set(PLATFORM_SUBDIR "linux-x86_64")
elseif(WIN32)
    set(PLATFORM_SUBDIR "windows-x64")
else()
    set(PLATFORM_SUBDIR "")
endif()

# For Developer builds (using DEV_MODE)
set(DEV_MODULES_PATH "lib/modules")
set(DEV_LIBS_PATH "lib/${PLATFORM_SUBDIR}")

message(STATUS "Found platform libraries to install at: ${DEV_LIBS_PATH}")

if(IS_MACOS_BUNDLE)
    set(INSTALL_MODULES_DEST "Resources/modules")
    set(INSTALL_LIBS_DEST "Resources")
else()
    set(INSTALL_MODULES_DEST "share/flowwing/modules")
    set(INSTALL_LIBS_DEST "lib/flowwing")
endif()

# =============================================================================
# 3. Define Sources and Executable Target
# =============================================================================

# Add a custom target for version information
add_custom_target(version
    COMMAND ${CMAKE_COMMAND} -DVERSION=${PROJECT_VERSION} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake
    COMMENT "Generating version information"
)

set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE EXECUTABLE_SOURCES "${MAIN_SRC_DIR}/**.cpp")

# If tests are enabled, add test sources and adjust the executable name
if(TESTS_ENABLED)
    set(MAIN_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    file(GLOB_RECURSE TEST_SOURCES "${MAIN_TESTS_DIR}/**.cpp")
    list(APPEND EXECUTABLE_SOURCES ${TEST_SOURCES})
    set(EXECUTABLE_NAME "runTests")
else()
    set(EXECUTABLE_NAME "FlowWing")
endif()

if(IS_MACOS_BUNDLE)
    # This tells CMake to create a .app bundle structure on macOS
    add_executable(${EXECUTABLE_NAME} MACOSX_BUNDLE ${EXECUTABLE_SOURCES})
else()
    # This is the original behavior for all other platforms (Linux, Windows)
    add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})
endif()

if(IS_MACOS_BUNDLE)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        OUTPUT_NAME "FlowWing"

        # This file is required for all macOS apps. You will need to create it.
        # It contains metadata like the app's identifier, version, etc.
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist
    )
else()
    # Ensure the final output binary is always named "FlowWing", even for test builds
    # set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME "FlowWing")
endif()

if(TESTS_ENABLED)
    # 1. Enable testing for this project.
    # This MUST be called before any add_test() commands.
    enable_testing()

    # 2. Register your test executable with CTest.
    # NAME:    The name that will appear in the test results.
    # COMMAND: The executable to run. We use the variable we already defined.
    add_test(NAME FlowWing-GTest COMMAND ${EXECUTABLE_NAME} --gtest_color=yes)
endif()

# Make the version target a dependency for non-test builds
add_dependencies(${EXECUTABLE_NAME} version)

# =============================================================================
# 4. Configure Target-Specific Properties
# =============================================================================

# --- Include Directories ---
target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${LLVM_INCLUDE_DIRS}
)

# --- Compile Definitions ---
if(BUILD_AOT)
    # AOT Mode Definitions
    if(TESTS_ENABLED)
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE AOT_TEST_MODE)
    else()
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE AOT_MODE)
    endif()
else()
    # JIT Mode Definitions
    if(TESTS_ENABLED)
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE JIT_TEST_MODE)
    else()
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE JIT_MODE)
    endif()
endif()

# Generic build-type and LLVM definitions
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
    ${LLVM_DEFINITIONS}

    # Pass the path map to the C++ code
    "DEV_MODULES_PATH=\"${DEV_MODULES_PATH}\""
    "DEV_LIBS_PATH=\"${DEV_LIBS_PATH}\""
    "INSTALL_MODULES_PATH=\"${INSTALL_MODULES_DEST}\""
    "INSTALL_LIBS_PATH=\"${INSTALL_LIBS_DEST}\""

    # Pass other necessary info
    "AOT_LINKER_PATH=\"${AOT_LINKER_PATH}\""

    "DEV_MODE_PATH=\"${CMAKE_SOURCE_DIR}\""
)

# --- Compile Options / Flags ---
target_compile_options(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g -fsanitize=undefined>
    $<$<CONFIG:Release>:-O3>
)

# --- Linker Options / Flags ---
target_link_options(${EXECUTABLE_NAME} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=undefined>

    # NOTE: The -fsanitize=address was only in one file. Add it here if needed for all debug builds.
    # $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

# --- Link Libraries ---
llvm_map_components_to_libnames(LLVM_STATIC_LIBRARIES
    core
    executionengine
    orcjit
    native
    interpreter
    mcjit
    target
    analysis
    aarch64info
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    ${LLVM_STATIC_LIBRARIES}
    Threads::Threads
)

if(TESTS_ENABLED)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${GTest_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gtest_main)
endif()

# =============================================================================
# 5. Installation and Packaging
# =============================================================================

# Install the final binary to 'bin'
if(IS_MACOS_BUNDLE)
    install(TARGETS ${EXECUTABLE_NAME} BUNDLE DESTINATION .)
else()
    install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
endif()

# 4. Install the language modules (.fg files) for ALL builds
# This installs the 'modules' folder into 'share/FlowWing/modules folder
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DEV_MODULES_PATH}/
    DESTINATION ${INSTALL_MODULES_DEST}
)

# 5. Install the shared libraries (.so, .a, .dll)
# This installs them into a 'lib/FlowWing' directory in the final package
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

# --- CPack Configuration ---
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Kushagra Rathore")
set(CPACK_PACKAGE_CONTACT "kushagrarathore002@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, simple, and easy to use programming language.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_EXECUTABLES "FlowWing" "FlowWing")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/release")

# Use the "DragNDrop" generator on macOS to create a user-friendly DMG
# --- Platform-Specific CPack Generators ---
if(WIN32)
    # Create a user-friendly NSIS installer on Windows
    set(CPACK_GENERATOR "NSIS")

# You can add an icon and start menu shortcuts here later
# set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/path/to/icon.ico")
# set(CPACK_NSIS_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/path/to/icon.ico")
# set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '$SMPROGRAMS\\FlowWing.lnk' '$INSTDIR\\bin\\FlowWing.exe'")
# set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/path/to/your/icon.ico")
elseif(APPLE)
    # Use the "DragNDrop" generator on macOS to create a user-friendly DMG
    set(CPACK_GENERATOR "DragNDrop")

elseif(UNIX)
    # Default to creating a .deb package on Linux
    set(CPACK_GENERATOR "DEB")
endif()

include(CPack)
