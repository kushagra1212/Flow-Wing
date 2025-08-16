# Defines the 'built_in_module' static library target.
add_library(built_in_module STATIC
    built_in_module.c
)


add_compile_definitions(
   built_in_module 
   PRIVATE
   GC_NOT_DLL
)

# This module needs to know where the Boehm GC headers are.
target_include_directories(built_in_module PRIVATE
    ${DEPS_INCLUDE_DIR}
)