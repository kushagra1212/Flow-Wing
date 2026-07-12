# Defines the 'built_in_module' static library target.
add_library(built_in_module STATIC
    built_in_module.c
)

target_link_libraries(built_in_module PRIVATE flowwing_gc)