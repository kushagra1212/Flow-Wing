# Defines the 'flowwing_vortex' static library target.
add_library(flowwing_vortex STATIC
    libflowwing_vortex.cpp
    uv_http_server.cpp
)

# llhttp: HTTP/1.1 parsing only. Sockets, response writing, chunked encoding
# and keep-alive are Flow-Wing's own code in uv_http_server.cpp.
set(_FW_SAVED_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)
find_library(LLHTTP_LIB NAMES llhttp PATHS "${DEPS_INSTALL_DIR}/lib" NO_DEFAULT_PATH REQUIRED)
set(CMAKE_FIND_LIBRARY_SUFFIXES ${_FW_SAVED_SUFFIXES})
message(STATUS "llhttp (static) for vortex: ${LLHTTP_LIB}")

target_include_directories(flowwing_vortex PUBLIC ${DEPS_INCLUDE_DIR})

# llhttp is small and used only here, so it is merged into this archive. Unlike
# libuv it is NOT needed by any other module, so there is no duplicate-symbol
# risk from force_load.
if(APPLE)
    add_custom_command(TARGET flowwing_vortex POST_BUILD
        COMMAND libtool -static -o $<TARGET_FILE:flowwing_vortex>
                $<TARGET_FILE:flowwing_vortex> ${LLHTTP_LIB}
        COMMENT "Merging llhttp into flowwing_vortex")
elseif(UNIX AND NOT APPLE)
    add_custom_command(TARGET flowwing_vortex POST_BUILD
        COMMAND ar -x $<TARGET_FILE:flowwing_vortex>
        COMMAND ar -x ${LLHTTP_LIB}
        COMMAND ar -rcs $<TARGET_FILE:flowwing_vortex> *.o
        COMMAND rm -f *.o
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Merging llhttp into flowwing_vortex using ar")
elseif(WIN32)
    target_link_libraries(flowwing_vortex PUBLIC ${LLHTTP_LIB})
endif()

# libuv gives the task scheduler something it cannot do by itself: idle on a
# SOCKET as well as a clock. Without it a task calling accept() parks the whole
# thread and no other task runs.
#
# libuv is NOT merged in here — flowwing_uv owns it. Two force-loaded archives
# each carrying libuv produce a duplicate definition of every uv_* symbol.
target_link_libraries(flowwing_vortex PRIVATE flowwing_gc PUBLIC flowwing_uv)
