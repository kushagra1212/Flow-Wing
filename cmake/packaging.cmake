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