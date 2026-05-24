#
# FlowWing Compiler
# Copyright (C) 2023-2026 Kushagra Rathore
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

add_library(flowwing_mongo STATIC libflowwing_mongo.cpp)

# mongo-c-driver 2.3.0 installs as libmongoc2.a / libbson2.a on Unix
# (verified via .fw_dependencies/install/lib) and mongoc2.lib / bson2.lib on
# Windows. Headers under include/mongoc-2.3.0 + bson-2.3.0. Use explicit
# filenames so cmake doesn't pick the sibling .dylib on macOS.
if(WIN32)
    # mongo-c-driver 2.x with BUILD_SHARED_LIBS=OFF installs mongoc2.lib /
    # bson2.lib; older 1.x layouts produced mongoc-static-1.0 / bson-static-1.0,
    # try both as a fallback. cmake adds the .lib suffix automatically.
    set(_MONGOC_LIB_NAMES mongoc2 mongoc-static-2.0)
    set(_BSON_LIB_NAMES   bson2   bson-static-2.0)
else()
    set(_MONGOC_LIB_NAMES libmongoc2.a)
    set(_BSON_LIB_NAMES   libbson2.a)
endif()
find_library(MONGOC_LIB NAMES ${_MONGOC_LIB_NAMES} PATHS "${DEPS_INSTALL_DIR}/lib" NO_DEFAULT_PATH REQUIRED)
find_library(BSON_LIB   NAMES ${_BSON_LIB_NAMES}   PATHS "${DEPS_INSTALL_DIR}/lib" NO_DEFAULT_PATH REQUIRED)

target_include_directories(flowwing_mongo PUBLIC
    "${DEPS_INSTALL_DIR}/include/mongoc-2.3.0"
    "${DEPS_INSTALL_DIR}/include/bson-2.3.0"
)

# libbson 2.x public typedef loses an alignment attribute on bson_t*; runtime
# pointers are correctly aligned. Suppress the spurious clang diagnostic.
target_compile_options(flowwing_mongo PRIVATE -Wno-align-mismatch)

if(APPLE)
    add_custom_command(TARGET flowwing_mongo POST_BUILD
        COMMAND libtool -static -o $<TARGET_FILE:flowwing_mongo>
                $<TARGET_FILE:flowwing_mongo>
                ${MONGOC_LIB}
                ${BSON_LIB}
        COMMENT "Merging libmongoc + libbson into flowwing_mongo"
    )
    target_link_libraries(flowwing_mongo PUBLIC
        "-framework CoreFoundation"
        "-framework Security"
        resolv
    )
elseif(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(flowwing_mongo PUBLIC
        ${MONGOC_LIB}
        ${BSON_LIB}
        ${OPENSSL_LIBRARIES}
        Threads::Threads
        resolv
        m
        dl
    )
    add_custom_command(TARGET flowwing_mongo POST_BUILD
        COMMAND ar -x $<TARGET_FILE:flowwing_mongo>
        COMMAND ar -x ${MONGOC_LIB}
        COMMAND ar -x ${BSON_LIB}
        COMMAND ar -rcs $<TARGET_FILE:flowwing_mongo> *.o
        COMMAND rm *.o
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Merging libmongoc + libbson into flowwing_mongo using ar"
    )
elseif(WIN32)
    target_link_libraries(flowwing_mongo PUBLIC
        ${MONGOC_LIB}
        ${BSON_LIB}
        ws2_32
        secur32
        crypt32
        dnsapi
    )
endif()
