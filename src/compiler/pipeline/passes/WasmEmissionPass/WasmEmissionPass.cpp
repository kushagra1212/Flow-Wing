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

#include "src/IRGen/LLVMBackendContext/LLVMBackendContext.hpp"
#include "WasmEmissionPass.hpp"
#include "src/IRGen/io/ObjectUtils.hpp"
#include "src/IRGen/io/Utils.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include <filesystem>
#include <system_error>

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace compiler {
namespace pipeline {

std::string WasmEmissionPass::getName() const { return "Wasm Emission"; }

// The wasm32 counterpart of ObjectEmissionPass.
//
// The bundled LLVM cannot generate WebAssembly, so each unit is written as
// LLVM bitcode, at the path its object file would have. emcc's linker compiles
// bitcode inputs itself (its standard -flto path), so everything that tracks
// object files, such as the list of brought units, works unchanged.
//
// The module keeps the triple and data layout IR generation gave it.
// ObjectUtils::createObjectFile must not be used here: it overwrites both with
// the host's, which is how a wasm32 build once became a native binary laid
// out for 32-bit pointers.
ReturnStatus WasmEmissionPass::run(CompilationContext &context) {
  llvm::Module *module = context.getBackendContext()->getLLVMModule();
  const std::string path = ir_gen::ObjectUtils::getObjectFilePath(
      context.getAbsoluteSourceFilePath(), context.getOptions().output_dir);
  ir_gen::Utils::createDirectories(
      std::filesystem::path(path).parent_path().string());

  std::error_code error;
  llvm::raw_fd_ostream out(path, error);
  if (error) {
    cli::Reporter::error("Could not write " + path + ": " + error.message());
    return ReturnStatus::kFailure;
  }
  llvm::WriteBitcodeToFile(*module, out);
  out.close();
  if (out.has_error()) {
    cli::Reporter::error("Could not write " + path + ": " +
                         out.error().message());
    out.clear_error();
    return ReturnStatus::kFailure;
  }
  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
