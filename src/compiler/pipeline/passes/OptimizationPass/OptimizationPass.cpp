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
#include "OptimizationPass.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"

// LLVM's own headers do not compile clean under this project's
// -Werror -Wconversion settings. llvm/Passes/PassBuilder.h reaches
// llvm/ADT/BitVector.h, which alone raises about twenty sign-conversion and
// 64-to-32 truncation errors. The push/pop pair silences them for these
// includes only; our own code below keeps every warning.
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm/Analysis/CGSCCPassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"

namespace flow_wing {
namespace compiler {
namespace pipeline {

void optimizeModule(llvm::Module &module, llvm::TargetMachine *target_machine,
                    OptimizationLevel level) {
  // LLVM asserts if buildPerModuleDefaultPipeline is asked for O0, which has
  // its own builder. There is nothing to do at O0 anyway.
  if (level == OptimizationLevel::O0) {
    return;
  }

  llvm::OptimizationLevel llvm_level = llvm::OptimizationLevel::O2;
  switch (level) {
  case OptimizationLevel::O1:
    llvm_level = llvm::OptimizationLevel::O1;
    break;
  case OptimizationLevel::O2:
    llvm_level = llvm::OptimizationLevel::O2;
    break;
  case OptimizationLevel::O3:
    llvm_level = llvm::OptimizationLevel::O3;
    break;
  case OptimizationLevel::O0:
    return;
  }

  llvm::LoopAnalysisManager loop_analysis;
  llvm::FunctionAnalysisManager function_analysis;
  llvm::CGSCCAnalysisManager cgscc_analysis;
  llvm::ModuleAnalysisManager module_analysis;

  // Passing the TargetMachine makes the pipeline target-aware, so inlining,
  // unrolling and vectorization decide against the real CPU rather than
  // against defaults.
  llvm::PassBuilder pass_builder(target_machine);
  pass_builder.registerModuleAnalyses(module_analysis);
  pass_builder.registerCGSCCAnalyses(cgscc_analysis);
  pass_builder.registerFunctionAnalyses(function_analysis);
  pass_builder.registerLoopAnalyses(loop_analysis);
  pass_builder.crossRegisterProxies(loop_analysis, function_analysis,
                                    cgscc_analysis, module_analysis);

  llvm::ModulePassManager module_passes =
      pass_builder.buildPerModuleDefaultPipeline(llvm_level);
  module_passes.run(module, module_analysis);
}

std::string OptimizationPass::getName() const { return "Optimization"; }

ReturnStatus OptimizationPass::run(CompilationContext &context) {

  llvm::Module *llvm_module = context.getBackendContext()->getLLVMModule();
  if (llvm_module == nullptr) {
    return ReturnStatus::kSuccess;
  }

  optimizeModule(*llvm_module, context.getBackendContext()->getTargetMachine(),
                 context.getOptions().optimization_level);

  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
