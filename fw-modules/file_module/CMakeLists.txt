# Defines the 'flowwing_file' static library target.
add_library(flowwing_file STATIC
    libflowwing_file.cpp
)

if(WIN32)
    add_compile_definitions(
        flowwing_file
        PRIVATE
        GC_NOT_DLL
    )
endif()

target_include_directories(flowwing_file PRIVATE
    ${DEPS_INCLUDE_DIR}
)
