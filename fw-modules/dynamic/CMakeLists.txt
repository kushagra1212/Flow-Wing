# Defines the 'dynamic' static library target.
add_library(dynamic STATIC
    dynamic.c
)

if(WIN32)
    add_compile_definitions(
        dynamic
        PRIVATE
        GC_NOT_DLL
    )
endif()

# This module needs to know where the Boehm GC headers are.
target_include_directories(dynamic PRIVATE
    ${DEPS_INCLUDE_DIR}
)