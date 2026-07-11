# Defines the 'flowwing_io' static library target.
add_library(flowwing_io STATIC
    libflowwing_io.cpp
)

target_link_libraries(flowwing_io PRIVATE flowwing_gc)
