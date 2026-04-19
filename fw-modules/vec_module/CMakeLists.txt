# Defines the 'flowwing_vec' static library target.
add_library(flowwing_vec STATIC
    libflowwing_vec.cpp
)

if(WIN32)
    add_compile_definitions(
        flowwing_vec
        PRIVATE 
        GC_NOT_DLL
    )
endif()

target_include_directories(flowwing_vec PRIVATE
    ${DEPS_INCLUDE_DIR}
)
