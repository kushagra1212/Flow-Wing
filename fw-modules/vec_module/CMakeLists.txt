# Defines the 'flowwing_vec' static library target.
add_library(flowwing_vec STATIC
    libflowwing_vec.cpp
)

target_link_libraries(flowwing_vec PRIVATE flowwing_gc)
