# Defines the 'flowwing_vortex' static library target.
add_library(flowwing_vortex STATIC
    libflowwing_vortex.cpp
)

target_link_libraries(flowwing_vortex PRIVATE flowwing_gc)
