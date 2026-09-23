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

#pragma once

#include <filesystem>
#include <string>

namespace flow_wing {
namespace linker {

// Everything outside this compiler that a wasm32 executable needs.
//
// The bundled LLVM has no WebAssembly backend (LLVM_TARGETS_TO_BUILD=Native),
// so for wasm32 the compiler writes LLVM bitcode and emcc does the rest: its
// linker compiles the bitcode and links it with the Flow-Wing runtime, which
// `make build-wasm-runtime` compiles to wasm once.
struct EmscriptenToolchain {
  // The emcc to run.
  std::string emcc;
  // emcc needs Python 3.10 or newer, which macOS does not ship. When emcc was
  // found through an emsdk folder rather than on PATH, this is emsdk's own
  // python3, passed as EMSDK_PYTHON the way emsdk_env.sh does it. Empty when
  // the environment is already set up.
  std::string emsdk_python;
  // <sdk>/lib/wasm32-emscripten: libflowwing_rt.a and node-stdio.js.
  std::filesystem::path runtime_dir;
  // Empty when everything was found; otherwise what the user should do.
  std::string problem;

  // Looks, in order: FLOWWING_EMCC, emcc on PATH, $EMSDK, ~/emsdk.
  static EmscriptenToolchain find();

  // em++, which sits next to emcc. The link runs through it rather than
  // emcc: the runtime's vec, map and io modules are C++, and only the C++
  // driver links the C++ standard library (operator new, std::cout, ...).
  // Every input the link sees is bitcode or an archive, so emcc cannot tell.
  std::string linkerDriver() const;

  std::filesystem::path runtimeArchive() const;
  std::filesystem::path nodeStdioScript() const;
};

} // namespace linker
} // namespace flow_wing
