# Defines the 'flowwing_map' static library target.
add_library(flowwing_map STATIC
    libflowwing_map.cpp
)

if(WIN32)
    add_compile_definitions(
        flowwing_map
        PRIVATE
        GC_NOT_DLL
    )
endif()

target_include_directories(flowwing_map PRIVATE
    ${DEPS_INCLUDE_DIR}
)
