# Defines 'flowwing_uv': the single archive that owns libuv.
#
# Every other module that needs an event loop links against this target and
# references the uv_* symbols. None of them merge libuv themselves — see the
# comment in fw_uv.c for why that would break the JIT link.

add_library(flowwing_uv STATIC fw_uv.c)

# fw_uv.c installs the scheduler's idle waiter, so it needs the scheduler API.
target_link_libraries(flowwing_uv PUBLIC flowwing_gc)

# Force the STATIC archive. libuv installs both libuv.a and libuv.dylib, and
# find_library prefers the shared one on macOS — which cannot be merged into
# this archive and would leave AOT executables needing a .dylib at run time.
set(_FW_SAVED_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)
find_library(LIBUV_LIB NAMES uv_a uv libuv PATHS "${DEPS_INSTALL_DIR}/lib" NO_DEFAULT_PATH REQUIRED)
set(CMAKE_FIND_LIBRARY_SUFFIXES ${_FW_SAVED_SUFFIXES})
message(STATUS "libuv (static) owned by flowwing_uv: ${LIBUV_LIB}")

# DEPS_INCLUDE_DIR gives uv.h; the source dir gives fw_uv.h. Both are PUBLIC so
# any module linking flowwing_uv can include either.
target_include_directories(flowwing_uv PUBLIC
    ${DEPS_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(flowwing_uv PROPERTIES C_STANDARD 11)

if(APPLE)
    add_custom_command(TARGET flowwing_uv POST_BUILD
        COMMAND libtool -static -o $<TARGET_FILE:flowwing_uv>
                $<TARGET_FILE:flowwing_uv>
                ${LIBUV_LIB}
        COMMENT "Merging libuv into flowwing_uv"
    )
elseif(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(flowwing_uv PUBLIC ${CMAKE_THREAD_LIBS_INIT} dl rt)
    add_custom_command(TARGET flowwing_uv POST_BUILD
        COMMAND ar -x $<TARGET_FILE:flowwing_uv>
        COMMAND ar -x ${LIBUV_LIB}
        COMMAND ar -rcs $<TARGET_FILE:flowwing_uv> *.o
        COMMAND rm -f *.o
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Merging libuv into flowwing_uv using ar"
    )
elseif(WIN32)
    target_link_libraries(flowwing_uv PUBLIC ${LIBUV_LIB}
        ws2_32 iphlpapi userenv dbghelp ole32 shell32)
endif()
