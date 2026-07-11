# Defines the 'flowwing_gc' static library target (Flow-Wing custom GC).
add_library(flowwing_gc STATIC
    src/fw_gc_header.c
    src/fw_gc_core.c
    src/fw_gc_mark.c
    src/fw_gc_sweep.c
    src/fw_gc_descriptors.c
    src/fw_gc_conservative.c
)

target_include_directories(flowwing_gc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(flowwing_gc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(flowwing_gc PROPERTIES C_STANDARD 11)
