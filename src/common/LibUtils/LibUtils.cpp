/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "LibUtils.h"

#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/utils/LogConfig.h"

namespace {

std::string getRuntimeLibraryForModule(const std::string &file_name) {

  LINKING_DEBUG_LOG("Checking runtime library for module: ", file_name.c_str());

  if (file_name == "text-module.fg") {
    return "flowwing_text";
  }

  if (file_name == "map-module.fg") {
    return "flowwing_map";
  }

  if (file_name == "vec-module.fg") {
    return "flowwing_vec";
  }

  if (file_name == "file-module.fg") {
    // Reads inside a task go through libuv's threadpool, so flowwing_uv must
    // follow flowwing_file: static link order decides resolution.
    //
    // A string containing a space is passed to the linker VERBATIM by
    // LinkerCommandBuilder, bypassing getLibLinkFlag. That is why each
    // platform spells its own flags here: MSVC wants "name.lib", not "-lname".
#if defined(_WIN32)
    // uv_a.lib is libuv itself. Windows has no archive-merge step, so it must
    // be named on the link line rather than folded into flowwing_uv.lib.
    return "flowwing_file.lib flowwing_uv.lib uv_a.lib "
           "ws2_32.lib iphlpapi.lib userenv.lib dbghelp.lib";
#elif defined(__linux__)
    return "-lflowwing_file -lflowwing_uv -lpthread -ldl -lrt";
#else
    return "-lflowwing_file -lflowwing_uv";
#endif
  }
  if (file_name == "io-module.fg") {
    return "flowwing_io";
  }
  if (file_name == "vortex-module.fg") {
    // flowwing_uv carries libuv and must follow flowwing_vortex: static link
    // order decides resolution, and vortex is the one referencing uv_*.
    //
    // libuv is a separate archive on purpose. The JIT build force-loads every
    // module archive, so merging libuv into more than one would define every
    // uv_* symbol twice.
    // Spelled per platform for the same reason as file-module above: a string
    // with a space skips getLibLinkFlag and reaches the linker unchanged.
    // libuv needs the Winsock and related system libraries on Windows.
#if defined(_WIN32)
    // uv_a.lib and llhttp.lib are the real libraries: on Windows they are not
    // merged into the flowwing_* archives, so they are named explicitly.
    return "flowwing_vortex.lib flowwing_uv.lib uv_a.lib llhttp.lib "
           "ws2_32.lib iphlpapi.lib userenv.lib dbghelp.lib "
           "ole32.lib shell32.lib advapi32.lib";
#elif defined(__linux__)
    return "-lflowwing_vortex -lflowwing_uv -lpthread -ldl -lrt";
#else
    return "-lflowwing_vortex -lflowwing_uv";
#endif
  }

  if (file_name == "raylib-module.fg") {

#if defined(__APPLE__)
    return "-lflowwing_raylib -framework CoreVideo -framework IOKit "
           "-framework Cocoa -framework GLUT -framework OpenGL";
#else
    return "flowwing_raylib";
#endif
  }

  if (file_name == "mongo-module.fg") {

#if defined(__APPLE__)
    return "-lflowwing_mongo -framework CoreFoundation -framework Security "
           "-lresolv";

#elif defined(_WIN32)

    return "flowwing_mongo.lib mongoc2.lib bson2.lib "
           "ws2_32.lib secur32.lib crypt32.lib dnsapi.lib "
           "bcrypt.lib ncrypt.lib";
#else

    return "-lflowwing_mongo -lssl -lcrypto -lpthread -lresolv -lm -ldl";
#endif
  }
  return "";
}

} // namespace

const char *STATIC_LINKING_LIBRARIES[3] = {"built_in_module", "dynamic",
                                           "flowwing_gc"};

std::vector<std::string>
getRuntimeLibrariesForSourceFile(const std::string &source_file_path) {
  std::vector<std::string> libraries;
  const std::string file_name =
      flow_wing::utils::PathUtils::getFileName(source_file_path);
  const std::string runtime_library = getRuntimeLibraryForModule(file_name);
  if (!runtime_library.empty()) {
    libraries.emplace_back(runtime_library);
  }
  return libraries;
}
