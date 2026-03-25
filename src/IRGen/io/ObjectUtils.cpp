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


#include "ObjectUtils.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/io/Utils.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/common/io/PathUtils.hpp"
#include "src/common/utils/PathUtils/PathUtils.h"
#include "src/utils/LogConfig.h"
#include <filesystem>
// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm-c/Core.h"
#include "llvm-c/TargetMachine.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace ir_gen {

std::string ObjectUtils::getObjectFilePath(const std::string &file_path,
                                           const std::string &output_dir) {
  // Canonicalize so the same file always maps to one object path (e.g. avoid
  // /Users/... vs /private/var/... mismatches between emit and link).
  std::string key = utils::PathUtils::getAbsoluteFilePath(file_path);
  if (!key.empty() && key[0] == '/') {
    key.erase(0, 1);
  }
  const std::string base =
      output_dir.empty() ? std::string("./build") : output_dir;
  std::filesystem::path rel =
      std::filesystem::absolute(base) / "objects" /
      std::filesystem::path(key +
                              std::string(constants::paths::kObject_file_extension));
  return rel.string();
}

bool ObjectUtils::createObjectFile(const llvm::Module *llvm_module,
                                   const std::string &file_path,
                                   const std::string &output_dir) {

  LLVMModuleRef module = wrap(llvm_module);

  char *errors = nullptr;
  LLVMTargetRef target;
  LLVMGetTargetFromTriple(LLVMGetDefaultTargetTriple(), &target, &errors);

  if (errors) {
    LLVMDisposeMessage(errors);
  }

  LLVMGetTargetFromTriple(LLVMGetDefaultTargetTriple(), &target, &errors);

  if (errors) {
    cli::Reporter::error("Failed to get target from triple: " +
                         std::string(errors));
    LLVMDisposeMessage(errors);
    return false;
  }

  CODEGEN_DEBUG_LOG("Target Name: ", LLVMGetTargetName(target));
  CODEGEN_DEBUG_LOG("Target Description: ", LLVMGetTargetDescription(target));
  CODEGEN_DEBUG_LOG("Target Has JIT: ", LLVMTargetHasJIT(target));
  CODEGEN_DEBUG_LOG("Target Has Target Machine: ",
                    LLVMTargetHasTargetMachine(target));
  CODEGEN_DEBUG_LOG("Triple: ", LLVMGetDefaultTargetTriple());
  CODEGEN_DEBUG_LOG("Features: ", LLVMGetHostCPUFeatures());

  LLVMTargetMachineRef machine = LLVMCreateTargetMachine(
      target, LLVMGetDefaultTargetTriple(), LLVMGetHostCPUName(),
      LLVMGetHostCPUFeatures(), LLVMCodeGenLevelDefault,
      LLVMRelocMode::LLVMRelocPIC, LLVMCodeModel::LLVMCodeModelDefault);

  LLVMSetTarget(module, LLVMGetDefaultTargetTriple());
  LLVMTargetDataRef datalayout = LLVMCreateTargetDataLayout(machine);
  char *datalayout_str = LLVMCopyStringRepOfTargetData(datalayout);

  CODEGEN_DEBUG_LOG("datalayout: ", datalayout_str);

  LLVMSetDataLayout(module, datalayout_str);
  LLVMDisposeMessage(datalayout_str);

  const std::string object_file_path = getObjectFilePath(file_path, output_dir);
  std::filesystem::path output_directory =
      std::filesystem::path(object_file_path).parent_path();

  Utils::createDirectories(output_directory.string());

  CODEGEN_DEBUG_LOG("Creating object ", object_file_path.c_str());

  errors = nullptr;
  const LLVMBool emit_failed = LLVMTargetMachineEmitToFile(
      machine, module, (char *)object_file_path.c_str(), LLVMObjectFile,
      &errors);
  if (emit_failed) {
    const std::string msg =
        errors ? std::string(errors) : std::string("unknown object emission error");
    if (errors) {
      LLVMDisposeMessage(errors);
    }
    cli::Reporter::error("Failed to emit object file '" + object_file_path +
                         "': " + msg);
    return false;
  }
  if (errors) {
    LLVMDisposeMessage(errors);
  }
  if (!std::filesystem::exists(object_file_path)) {
    cli::Reporter::error("Object file was not created at '" + object_file_path +
                         "'");
    return false;
  }
  return true;
}

} // namespace ir_gen
} // namespace flow_wing