# Defines the 'flowwing_gc' static library target (Flow-Wing custom GC).
add_library(flowwing_gc STATIC
    src/fw_gc_header.c
    src/fw_gc_core.c
    src/fw_gc_mark.c
    src/fw_gc_sweep.c
    src/fw_gc_descriptors.c
)

target_include_directories(flowwing_gc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(flowwing_gc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(flowwing_gc PROPERTIES C_STANDARD 11)

add_executable(test_gc tests/test_gc.c)
target_link_libraries(test_gc PRIVATE flowwing_gc)
target_include_directories(test_gc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
set_target_properties(test_gc PROPERTIES C_STANDARD 11)
