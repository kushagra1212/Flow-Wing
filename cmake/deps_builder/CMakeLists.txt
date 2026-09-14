#
# FlowWing Compiler
# Copyright (C) 2023-2025 Kushagra Rathore
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

cmake_minimum_required(VERSION 3.29)
project(DependencySuperbuild NONE)

include(ExternalProject)

set(LLVM_ASSERTIONS_SETTING OFF)
set(CMAKE_CONFIG_TYPE ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LLVM_ASSERTIONS_SETTING ON)
    message(STATUS "Configuring for a Debug build: LLVM Assertions ON.")
else()
    set(CMAKE_CONFIG_TYPE "Release") # Default to Release
    message(STATUS "Configuring for a Release build: LLVM Assertions OFF.")
endif()

set(DEPS_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/../install")
message("DEPS_INSTALL_DIR: ${DEPS_INSTALL_DIR}")

set(STAMP_FILE "${CMAKE_CURRENT_BINARY_DIR}/../stamps/.installed-${CMAKE_BUILD_TYPE}")
message("STAMP FILE: ${STAMP_FILE}")

if(EXISTS "${STAMP_FILE}")
    message(STATUS "Dependencies already built in ${DEPS_INSTALL_DIR}")
else()
   ExternalProject_Add(
        raylib_external
        GIT_REPOSITORY  "https://github.com/raysan5/raylib.git"
        GIT_TAG "5.5"
        GIT_SHALLOW TRUE
        CMAKE_ARGS 
            -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE}
            -DBUILD_EXAMPLES=OFF
            -DBUILD_GAMES=OFF
            -DCUSTOMIZE_BUILD=ON
            -DBUILD_SHARED_LIBS=OFF
            -DPLATFORM=Desktop
        USES_TERMINAL_DOWNLOAD true 
        USES_TERMINAL_CONFIGURE true 
        USES_TERMINAL_BUILD true 
        USES_TERMINAL_INSTALL true
        GIT_PROGRESS TRUE
    )

    # libuv — the event loop the task scheduler idles in.
    #
    # Without it the scheduler can only wait on a clock (nanosleep), so a task
    # that waits on a SOCKET blocks the whole thread and no other task runs.
    # uv_run waits on timers and sockets together, which is what lets a server
    # task park without stopping everything else.
    ExternalProject_Add(
        libuv_external
        GIT_REPOSITORY  "https://github.com/libuv/libuv.git"
        GIT_TAG         "v1.51.0"
        GIT_SHALLOW     TRUE
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE}
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DBUILD_SHARED_LIBS=OFF
            -DLIBUV_BUILD_TESTS=OFF
            -DLIBUV_BUILD_BENCH=OFF
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
        GIT_PROGRESS TRUE
    )

    # llhttp — the HTTP/1.1 parser Node.js uses.
    #
    # Parsing only: it turns bytes into request-line/header/body callbacks and
    # nothing else. Sockets, response writing, chunked encoding and keep-alive
    # stay in Flow-Wing's own code, which is the point — a parser is the one
    # part of HTTP that is genuinely hard to get right, and this one is
    # battle-tested.
    #
    # The release/ tags ship pre-generated C, so no TypeScript toolchain is
    # needed to build it.
    ExternalProject_Add(
        llhttp_external
        URL "https://github.com/nodejs/llhttp/archive/refs/tags/release/v9.2.1.tar.gz"
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE}
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DBUILD_SHARED_LIBS=OFF
            -DBUILD_STATIC_LIBS=ON
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
    )

    ExternalProject_Add(
        mongo_c_driver_external
        GIT_REPOSITORY  "https://github.com/mongodb/mongo-c-driver.git"
        # 2.3.3, not 2.3.0. 2.3.0's own src/libmongoc/CMakeLists.txt passes a
        # malformed argument to the accept() probe:
        #
        #   CMAKE_FLAGS "-Werror -DCMAKE_CXX_LINK_EXECUTABLE='echo not linking now...'"
        #
        # Both flags are one quoted string, so the inner cmake sees a single
        # argument, reads the leading -W and treats the rest as a warning
        # category name. CMake used to ignore an unknown category; newer
        # releases make it fatal, which broke the macOS runner (its Homebrew
        # cmake is ahead of the Linux one, and Windows never reaches the probe
        # because mongoc guards it with `if (NOT WIN32)`).
        #
        # 2.3.3 is the upstream fix — the string is split into two proper
        # arguments and -Werror moves into COMPILE_DEFINITIONS. Patch release
        # on the same minor line, so no API change for us.
        GIT_TAG         "2.3.3"
        GIT_SHALLOW     TRUE
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE}
            -DBUILD_SHARED_LIBS=OFF
            -DENABLE_TESTS=OFF
            -DENABLE_EXAMPLES=OFF
            -DENABLE_SASL=OFF
            -DENABLE_SRV=OFF
            -DENABLE_SNAPPY=OFF
            -DENABLE_ZSTD=OFF
            -DENABLE_ZLIB=BUNDLED
            -DENABLE_MONGOC=ON
            -DENABLE_BSON=ON
            -DENABLE_STATIC=ON
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
        GIT_PROGRESS TRUE
    )

    set(LLVM_BUILD_SHARED OFF)

    if(NOT WIN32)
        set(LLVM_BUILD_SHARED ON)
    endif()

    # =======================================================================
    # LLVM — downloaded as a prebuilt artifact, NOT built from source.
    #
    # Measured on a cold CI run: the whole dependency build took 66 minutes,
    # and 64 of them were LLVM (18:46 [1/3776] -> 19:40 [3776/3776]). Every
    # other dependency on this page finishes in 1m45s together. So LLVM is the
    # only one worth shipping prebuilt, and the others keep building from
    # source — which also means bumping libuv or llhttp costs nothing here.
    #
    # WHY NOT THE OFFICIAL llvm-project RELEASE TARBALL
    #
    #   We build with LLVM_ENABLE_RTTI=ON and LLVM_ENABLE_EH=ON. The official
    #   binaries are built with both OFF. FlowWing does link against an
    #   RTTI=OFF LLVM (verified: no undefined `typeinfo for llvm::` symbols in
    #   any of its objects), but publishing our own keeps the downloaded
    #   compiler byte-for-byte equivalent to a from-source build instead of
    #   quietly diverging.
    #
    # The artifact is produced by scripts/package-llvm-artifact.sh and holds
    # ONLY the LLVM/Clang/LLD part of the prefix, plus its Apache-2.0 licence.
    #
    # To go back to building from source — when bumping the LLVM version, or
    # when no artifact exists yet for a platform:
    #
    #   cmake -DFW_LLVM_FROM_SOURCE=ON ...
    # =======================================================================
    option(FW_LLVM_FROM_SOURCE
        "Build LLVM from source (~54 min) instead of downloading the prebuilt artifact" OFF)

    # The environment variable exists because the dependency build is driven
    # through `make deps-install-release`, which invokes a fixed CMake preset
    # and has no way to forward an extra -D. The artifact-building workflow
    # needs to force the source build, so it sets this instead. A -D on the
    # command line still wins when one is given.
    if(NOT FW_LLVM_FROM_SOURCE AND DEFINED ENV{FW_LLVM_FROM_SOURCE})
        if("$ENV{FW_LLVM_FROM_SOURCE}" MATCHES "^(1|ON|on|TRUE|true|YES|yes)$")
            set(FW_LLVM_FROM_SOURCE ON)
            message(STATUS "LLVM: FW_LLVM_FROM_SOURCE set in the environment")
        endif()
    endif()

    set(FW_LLVM_VERSION "17.0.6")
    set(FW_LLVM_RELEASE_TAG "deps-llvm-${FW_LLVM_VERSION}"
        CACHE STRING "GitHub release tag holding the prebuilt LLVM artifacts")
    set(FW_LLVM_RELEASE_BASE
        "https://github.com/kushagra1212/Flow-Wing/releases/download/${FW_LLVM_RELEASE_TAG}")

    if(NOT FW_LLVM_FROM_SOURCE)
        # Artifact names come from uname in the packaging script, so mirror
        # that here rather than inventing a second naming scheme.
        set(_FW_A_OS "${CMAKE_HOST_SYSTEM_NAME}")           # Darwin / Linux / Windows
        set(_FW_A_ARCH "${CMAKE_HOST_SYSTEM_PROCESSOR}")    # arm64 / x86_64 / AMD64
        set(_FW_ARTIFACT
            "llvm-${FW_LLVM_VERSION}-${_FW_A_OS}-${_FW_A_ARCH}-${CMAKE_CONFIG_TYPE}.tar.xz")

        # SHA-256 per artifact. A download is only ever taken when its hash is
        # recorded here — an unverified 100 MB binary dropped into the build
        # would be a far bigger risk than any flag on this page. A platform
        # with no entry falls back to the source build instead (see below).
        #
        # Produced by .github/workflows/build_deps_artifacts.yml, which prints
        # each hash in its job summary. Add a line when a platform gains one.
        set(_FW_SHA_Darwin-arm64-Release
            "2f9c10d3b9fdeaa7d84f8927c3db0ab948d61d4f15bd57fc6167344421dff7bc")
        set(_FW_SHA_Darwin-arm64-Debug
            "a5cba543ec2760c38be16cd56b7b0b370901ff48f7da374f232bdd3f862cad2e")
        # Linux-x86_64 and Windows-AMD64 have no artifacts published yet, so
        # they still compile LLVM. Publishing theirs is what makes them fast.

        set(_FW_SHA_KEY "_FW_SHA_${_FW_A_OS}-${_FW_A_ARCH}-${CMAKE_CONFIG_TYPE}")
        if(NOT DEFINED ${_FW_SHA_KEY})
            # Fall back to the source build rather than failing.
            #
            # A hard error here would break every platform that has no artifact
            # published yet — which is how this started life, and it meant the
            # change could not be landed before all six artifacts existed. A
            # source build is exactly the previous behaviour: slow, correct,
            # and no security downgrade, because the thing worth refusing is an
            # UNVERIFIED DOWNLOAD, not compiling from a pinned git tag.
            message(WARNING
                "No prebuilt LLVM artifact recorded for "
                "${_FW_A_OS}-${_FW_A_ARCH}-${CMAKE_CONFIG_TYPE} — "
                "falling back to building LLVM from source (~54 minutes).\n"
                "To make this fast: publish an artifact with "
                "scripts/package-llvm-artifact.sh and add its SHA-256 above.")
            set(FW_LLVM_FROM_SOURCE ON)
        else()
            message(STATUS "LLVM: downloading prebuilt ${_FW_ARTIFACT}")
        endif()
    endif()

    # Re-tested after the fallback above may have flipped it.
    if(NOT FW_LLVM_FROM_SOURCE)

        ExternalProject_Add(
            llvm_external
            URL "${FW_LLVM_RELEASE_BASE}/${_FW_ARTIFACT}"
            URL_HASH "SHA256=${${_FW_SHA_KEY}}"
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE

            # Nothing to configure or compile: the archive already IS the
            # install tree. Unpack it straight into the shared prefix.
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
                            <SOURCE_DIR> ${DEPS_INSTALL_DIR}

            USES_TERMINAL_DOWNLOAD true
            USES_TERMINAL_INSTALL true
        )
    else()
    message(STATUS "LLVM: building from source (this takes about 54 minutes)")
    ExternalProject_Add(
        llvm_external

        # --- REPLACED a URL download with a Git Clone ---
        GIT_REPOSITORY "https://github.com/llvm/llvm-project.git"
        GIT_TAG "llvmorg-${FW_LLVM_VERSION}"
        GIT_SHALLOW TRUE # Downloads only the history for that one tag

        # --- END REPLACEMENT ---
        SOURCE_SUBDIR llvm

        # IMPORTANT: CMAKE_ARGS is itself a CMake list, so a literal `;` inside a single
        # argument (like -DLLVM_ENABLE_PROJECTS=clang;lld) is interpreted as an outer list
        # separator — the sub-CMake only sees -DLLVM_ENABLE_PROJECTS=clang and the stray
        # token `lld` gets silently dropped, so LLD is NEVER built (no lld-link.exe, no
        # ld.lld, no ld64.lld). Use LIST_SEPARATOR to pick a non-semicolon character for
        # the outer list and substitute it back to `;` when the nested CMake is invoked.
        # See https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add
        LIST_SEPARATOR "|"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE} -DLLVM_ENABLE_PROJECTS=clang|lld -DLLVM_TARGETS_TO_BUILD=Native -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_ENABLE_ASSERTIONS=${LLVM_ASSERTIONS_SETTING} -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_EH=ON -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_EXAMPLES=OFF -DLLVM_INCLUDE_BENCHMARKS=OFF -DLLVM_BUILD_LLVM_DYLIB=${LLVM_BUILD_SHARED} -DLLVM_LINK_LLVM_DYLIB=${LLVM_BUILD_SHARED}
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true

        GIT_PROGRESS TRUE
    )
    endif()

    # Both branches above define a target called llvm_external, so everything
    # that depends on LLVM — gtest below, and the main build's find_package —
    # works the same whether it was downloaded or compiled.
    ExternalProject_Add(
        gtest_external
        DEPENDS llvm_external
        URL "https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz"
        URL_HASH "SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_CONFIG_TYPE} -DBUILD_GMOCK=OFF

     
        USES_TERMINAL_DOWNLOAD true
        USES_TERMINAL_CONFIGURE true
        USES_TERMINAL_BUILD true
        USES_TERMINAL_INSTALL true
    )
endif()