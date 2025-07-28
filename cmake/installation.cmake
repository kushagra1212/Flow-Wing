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