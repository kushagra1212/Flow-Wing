
add_library(flowwing_raylib STATIC libflowwing_raylib.cpp)

find_library(RAYLIB_LIB NAMES raylib PATHS "${DEPS_INSTALL_DIR}/lib" NO_DEFAULT_PATH)

if(APPLE)
    add_custom_command(TARGET flowwing_raylib POST_BUILD
        COMMAND libtool -static -o $<TARGET_FILE:flowwing_raylib>
                $<TARGET_FILE:flowwing_raylib>
                ${RAYLIB_LIB}
        COMMENT "Merging raylib into flowwing_raylib"
    )

    target_link_libraries(flowwing_raylib PUBLIC
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
elseif(UNIX AND NOT APPLE)
    # Standard Linux dependencies for raylib
    find_package(Threads REQUIRED)
    
    target_link_libraries(flowwing_raylib PUBLIC 
        ${RAYLIB_LIB}
        GL
        m
        pthread
        dl
        rt
        X11
    )

    # Merging static libraries on Linux
    add_custom_command(TARGET flowwing_raylib POST_BUILD
        COMMAND ar -x $<TARGET_FILE:flowwing_raylib>
        COMMAND ar -x ${RAYLIB_LIB}
        COMMAND ar -rcs $<TARGET_FILE:flowwing_raylib> *.o
        COMMAND rm *.o
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Merging raylib into flowwing_raylib using ar"
    )
elseif(WIN32)
    target_link_libraries(flowwing_raylib PUBLIC ${RAYLIB_LIB} winmm gdi32 shell32)
    target_compile_definitions(flowwing_raylib PRIVATE GC_NOT_DLL)
endif()

target_include_directories(flowwing_raylib PUBLIC ${DEPS_INCLUDE_DIR})