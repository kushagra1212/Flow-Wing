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

namespace {

std::string getRuntimeLibraryForModule(const std::string &file_name) {
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
    return "flowwing_file";
  }

  if (file_name == "vortex-module.fg") {
    return "flowwing_vortex";
  }

  if (file_name == "raylib-module.fg") {

#if defined(__APPLE__)
    return "flowwing_raylib -framework IOKit -framework Cocoa -framework "
           "OpenGL ";

#else
    return "flowwing_raylib";
#endif
  }
  return "";
}

} // namespace

const char *STATIC_LINKING_LIBRARIES[5] = {"built_in_module", "dynamic", "gc",
                                           "gccpp", "atomic_ops"};

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
