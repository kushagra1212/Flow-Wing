    add_library(flowwing_raylib STATIC
        libflowwing_raylib.cpp
    )

    set(RAYLIB_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libraylib.a")

    if(NOT EXISTS "${RAYLIB_LIB}")
        message(FATAL_ERROR "libraylib.a not found at: ${RAYLIB_LIB}")
    endif()

    if(APPLE)
        # Merge libraylib.a into libflowwing_raylib.a so the SDK only needs one lib
        add_custom_command(TARGET flowwing_raylib POST_BUILD
            COMMAND libtool -static -o $<TARGET_FILE:flowwing_raylib>
                    $<TARGET_FILE:flowwing_raylib>
                    ${RAYLIB_LIB}
            COMMENT "Merging libraylib.a into libflowwing_raylib.a"
        )

        target_link_libraries(flowwing_raylib PUBLIC
            "-framework IOKit"
            "-framework Cocoa"
            "-framework OpenGL"
        )
    endif()

    if(WIN32)
        target_compile_definitions(flowwing_raylib PRIVATE GC_NOT_DLL)
    endif()

    target_include_directories(flowwing_raylib PRIVATE
        ${DEPS_INCLUDE_DIR}
    )