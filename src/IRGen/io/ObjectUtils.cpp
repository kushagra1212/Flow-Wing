/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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
// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm-c/Core.h"
#include "llvm-c/TargetMachine.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {
namespace ir_gen {

std::string ObjectUtils::getObjectFilePath(const std::string &file_path) {
  return std::string(constants::paths::kObject_files_dir) + file_path +
         std::string(constants::paths::kObject_file_extension);
}

void ObjectUtils::createObjectFile(const llvm::Module *llvm_module,
                                   const std::string &file_path) {

  LLVMModuleRef module = wrap(llvm_module);

  char *errors = 0;
  LLVMTargetRef target;
  LLVMGetTargetFromTriple(LLVMGetDefaultTargetTriple(), &target, &errors);

  LLVMDisposeMessage(errors);

  LLVMGetTargetFromTriple(LLVMGetDefaultTargetTriple(), &target, &errors);

  if (errors) {
    cli::Reporter::error("Failed to get target from triple: " +
                         std::string(errors));
    LLVMDisposeMessage(errors);
    return;
  }

  LLVMDisposeMessage(errors);

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

  const std::string object_file_path = getObjectFilePath(file_path);
  std::filesystem::path output_directory =
      std::filesystem::path(object_file_path).parent_path();

  Utils::createDirectories(output_directory.string());

  CODEGEN_DEBUG_LOG("Creating object ", object_file_path.c_str());

  LLVMTargetMachineEmitToFile(machine, module, (char *)object_file_path.c_str(),
                              LLVMObjectFile, &errors);

  LLVMDisposeMessage(errors);
}

} // namespace ir_gen
} // namespace flow_wing