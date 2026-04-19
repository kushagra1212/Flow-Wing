# Defines the 'flowwing_vortex' static library target.
add_library(flowwing_vortex STATIC
    libflowwing_vortex.cpp
)

if(WIN32)
    add_compile_definitions(
        flowwing_vortex
        PRIVATE 
        GC_NOT_DLL
    )
endif()

target_include_directories(flowwing_vortex PRIVATE
    ${DEPS_INCLUDE_DIR}
)
