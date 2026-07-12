# Defines the 'flowwing_map' static library target.
add_library(flowwing_map STATIC
    libflowwing_map.cpp
)

target_link_libraries(flowwing_map PRIVATE flowwing_gc)
