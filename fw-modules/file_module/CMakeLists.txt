# Defines the 'flowwing_file' static library target.
add_library(flowwing_file STATIC
    libflowwing_file.cpp
)

# flowwing_uv owns libuv and the shared loop. File reads are pushed onto
# libuv's threadpool so a task waiting on disk does not park the thread.
target_link_libraries(flowwing_file PRIVATE flowwing_gc PUBLIC flowwing_uv)
