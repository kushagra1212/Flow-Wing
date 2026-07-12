# Defines the 'flowwing_file' static library target.
add_library(flowwing_file STATIC
    libflowwing_file.cpp
)

target_link_libraries(flowwing_file PRIVATE flowwing_gc)
