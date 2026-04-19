# Defines the 'flowwing_io' static library target.
add_library(flowwing_io STATIC
    libflowwing_io.cpp
)

if(WIN32)
    add_compile_definitions(
        flowwing_io 
        PRIVATE 
        GC_NOT_DLL
    )
endif()

target_include_directories(flowwing_io PRIVATE
    ${DEPS_INCLUDE_DIR}
)
