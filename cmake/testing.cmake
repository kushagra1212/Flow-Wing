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