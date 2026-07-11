# Defines the 'dynamic' static library target.
add_library(dynamic STATIC
    dynamic.c
)

target_link_libraries(dynamic PRIVATE flowwing_gc)