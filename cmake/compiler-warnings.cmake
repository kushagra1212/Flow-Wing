# =============================================================================
# Strict Compiler Warnings
#
# Enforces a high level of compiler warnings to improve code quality and
# catch potential errors early. Warnings are treated as errors.
# =============================================================================

if(MSVC)
    # /W4 is a high warning level, /WX treats warnings as errors
    set(PROJECT_WARNING_FLAGS "/W4 /WX")
else()
    # -Wall, -Wextra, -Wpedantic provide a comprehensive set of warnings
    # -Werror treats all warnings as errors
    set(PROJECT_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)
endif()

message(STATUS "Strict compiler warnings enabled: ${PROJECT_WARNING_FLAGS}")