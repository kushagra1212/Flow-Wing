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

#include "src/compiler/Linker/EmscriptenToolchain.hpp"

#include "src/common/io/PathUtils.hpp"
#include <cstdlib>
#include <optional>
#include <system_error>
#include <vector>

namespace flow_wing {
namespace linker {

namespace {

namespace fs = std::filesystem;

#if defined(_WIN32)
constexpr char kPathSeparator = ';';
constexpr const char *kEmccName = "emcc.bat";
constexpr const char *kEmxxName = "em++.bat";
#else
constexpr char kPathSeparator = ':';
constexpr const char *kEmccName = "emcc";
constexpr const char *kEmxxName = "em++";
#endif

std::string environment(const char *name) {
  const char *value = std::getenv(name);
  return value != nullptr ? std::string(value) : std::string();
}

bool isFile(const fs::path &path) {
  std::error_code error;
  return fs::is_regular_file(path, error);
}

std::optional<fs::path> findOnPath(const std::string &program) {
  const std::string path = environment("PATH");
  size_t start = 0;
  while (start <= path.size()) {
    const size_t end = path.find(kPathSeparator, start);
    const std::string dir =
        path.substr(start, end == std::string::npos ? std::string::npos
                                                     : end - start);
    if (!dir.empty() && isFile(fs::path(dir) / program)) {
      return fs::path(dir) / program;
    }
    if (end == std::string::npos) {
      break;
    }
    start = end + 1;
  }
  return std::nullopt;
}

// emsdk keeps its Python under python/<version>/bin/python3 (python.exe on
// Windows, without the bin folder).
std::string emsdkPython(const fs::path &emsdk_root) {
  std::error_code error;
  for (const auto &entry :
       fs::directory_iterator(emsdk_root / "python", error)) {
#if defined(_WIN32)
    const fs::path candidate = entry.path() / "python.exe";
#else
    const fs::path candidate = entry.path() / "bin" / "python3";
#endif
    if (isFile(candidate)) {
      return candidate.string();
    }
  }
  return "";
}

fs::path homeDirectory() {
#if defined(_WIN32)
  return fs::path(environment("USERPROFILE"));
#else
  return fs::path(environment("HOME"));
#endif
}

} // namespace

EmscriptenToolchain EmscriptenToolchain::find() {
  EmscriptenToolchain toolchain;
  toolchain.runtime_dir =
      io::PathUtils::getLibrariesPath().parent_path() / "wasm32-emscripten";

  // An explicit choice wins, and a wrong one is reported rather than
  // silently replaced by some other emcc.
  const std::string forced = environment("FLOWWING_EMCC");
  if (!forced.empty()) {
    toolchain.emcc = forced;
    if (!isFile(forced)) {
      toolchain.problem = "FLOWWING_EMCC points at '" + forced +
                          "', which does not exist.";
    } else if (!isFile(toolchain.linkerDriver())) {
      toolchain.problem = "No em++ next to FLOWWING_EMCC ('" +
                          toolchain.linkerDriver() + "').";
    }
    return toolchain;
  }

  if (auto on_path = findOnPath(kEmccName)) {
    toolchain.emcc = on_path->string();
    return toolchain;
  }

  std::vector<fs::path> emsdk_roots;
  if (const std::string emsdk = environment("EMSDK"); !emsdk.empty()) {
    emsdk_roots.emplace_back(emsdk);
  }
  emsdk_roots.push_back(homeDirectory() / "emsdk");

  for (const auto &root : emsdk_roots) {
    const fs::path emcc = root / "upstream" / "emscripten" / kEmccName;
    if (isFile(emcc)) {
      toolchain.emcc = emcc.string();
      toolchain.emsdk_python = emsdkPython(root);
      return toolchain;
    }
  }

  toolchain.problem =
      "--target=wasm32 --emit=exe needs Emscripten (emcc), which was not "
      "found.\n"
      "Install emsdk: https://emscripten.org/docs/getting_started/"
      "downloads.html\n"
      "Then put emcc on PATH (source emsdk_env.sh), set EMSDK to the emsdk "
      "folder, or set FLOWWING_EMCC to emcc itself.";
  return toolchain;
}

std::string EmscriptenToolchain::linkerDriver() const {
  return (fs::path(emcc).parent_path() / kEmxxName).string();
}

fs::path EmscriptenToolchain::runtimeArchive() const {
  return runtime_dir / "libflowwing_rt.a";
}

fs::path EmscriptenToolchain::nodeStdioScript() const {
  return runtime_dir / "node-stdio.js";
}

} // namespace linker
} // namespace flow_wing
