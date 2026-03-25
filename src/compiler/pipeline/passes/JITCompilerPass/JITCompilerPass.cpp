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

#include "JITCompilerPass.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/io/JITUtils.hpp"
#include "src/common/cli/CliReporter.h"
#include "src/common/io/FileUtils.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/pipeline/CompilationPipeline.h"
#include "src/compiler/pipeline/passes/IRGenerationPass/IRGenerationPass.hpp"
#include "src/compiler/pipeline/passes/LexerPass/LexerPass.h"
#include "src/compiler/pipeline/passes/ParsingPass/ParsingPass.h"
#include "src/compiler/pipeline/passes/SemanticAnalysisPass/SemanticAnalysisPass.hpp"
#include "src/compiler/pipeline/passes/SourceLoaderPass.h"
#include <cstdlib>

// clang-format off
#include "src/common/diagnostics/diagnostic_push.h"
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/Error.h"
#include <llvm/Support/SourceMgr.h>
#include "llvm/Target/TargetMachine.h"
#include "src/common/diagnostics/diagnostic_pop.h"
// clang-format on

namespace flow_wing {

namespace compiler {
namespace pipeline {

namespace {

/// After CleanupPass may have cleared the temp dir, (re)emit LLVM IR for each
/// `bring` dependency so the JIT session can resolve globals defined in other
/// translation units.
ReturnStatus compileBroughtSourcesToIRForJIT(CompilationContext &context) {
  const std::string &parent_ir_dir = context.getTempDirectoryPath();
  const auto &parent_opts = context.getOptions();
  for (const std::string &src_path : context.getBroughtSourcePaths()) {
    CompilerOptions dep_opts;
    dep_opts.input_file_path = src_path;
    dep_opts.output_dir = parent_opts.output_dir;
    dep_opts.optimization_level = parent_opts.optimization_level;
    dep_opts.enable_server = parent_opts.enable_server;
    dep_opts.enable_linker_warnings = parent_opts.enable_linker_warnings;
    dep_opts.emit_brought_dependency_object = 1;

    CompilationContext dep_ctx(dep_opts);
    CompilationPipeline pipeline;
    pipeline.addPass(std::make_unique<SourceLoaderPass>());
    pipeline.addPass(std::make_unique<LexerPass>());
    pipeline.addPass(std::make_unique<ParsingPass>());
    pipeline.addPass(std::make_unique<SemanticAnalysisPass>());
    pipeline.addPass(std::make_unique<IRGenerationPass>());
    if (pipeline.run(dep_ctx) != ReturnStatus::kSuccess) {
      return ReturnStatus::kFailure;
    }
    flow_wing::ir_gen::jit_utils::saveIRToFile(dep_ctx.getLLVMIr(), parent_ir_dir,
                                               dep_ctx.getAbsoluteSourceFilePath());
  }
  return ReturnStatus::kSuccess;
}

} // namespace

std::string JITCompilerPass::getName() const { return "JIT Compiler"; }

ReturnStatus JITCompilerPass::run(CompilationContext &context) {

  if (compileBroughtSourcesToIRForJIT(context) != ReturnStatus::kSuccess) {
    return ReturnStatus::kFailure;
  }

  // Save the Source IR to a file
  const std::string &ir_directory_path = context.getTempDirectoryPath();

  flow_wing::ir_gen::jit_utils::saveIRToFile(
      context.getLLVMIr(), ir_directory_path,
      context.getOptions().input_file_path);

  auto JITExpected = llvm::orc::LLJITBuilder().create();

  if (!JITExpected) {
    flow_wing::cli::Reporter::error("Failed to create JIT: ");
    return ReturnStatus::kFailure;
  }
  auto JIT = std::move(*JITExpected);

  // 3. Create a ThreadSafeContext.
  // ORC JIT requires modules to be wrapped in ThreadSafeModule for thread
  // safety. We share this context across modules for simplicity here.
  auto TSCtx = std::make_unique<llvm::orc::ThreadSafeContext>(
      std::make_unique<llvm::LLVMContext>());

  std::vector<std::string> ir_files = flow_wing::io::getFiles(
      ir_directory_path,
      std::string(flow_wing::ir_gen::constants::paths::kIR_files_extension));

  llvm::SMDiagnostic err;
  for (const std::string &path : ir_files) {
    LINKING_DEBUG_LOG(" [INFO]: Loading Module for JIT: ", path);

    // Parse IR into the Context
    auto module = llvm::parseIRFile(path, err, *TSCtx->getContext());

    if (!module) {
      flow_wing::cli::Reporter::error("Failed to parse IR file: " + path);
      return ReturnStatus::kFailure;
    }

    // Add the module to the JIT.
    // The JIT linker will automatically resolve symbols (like function calls)
    // between this module and previously added ones.
    llvm::Error addErr = JIT->addIRModule(
        llvm::orc::ThreadSafeModule(std::move(module), *TSCtx));

    if (addErr) {
      std::string errMsg;
      llvm::raw_string_ostream errStream(errMsg);
      errStream << addErr;
      flow_wing::cli::Reporter::error("JIT Error adding module: " + errMsg);
      return ReturnStatus::kFailure;
    }
  }

  auto SymExpected = JIT->lookup(
      std::string(flow_wing::ir_gen::constants::functions::kMain_fn));

  if (!SymExpected) {
    std::string errMsg;
    llvm::raw_string_ostream errStream(errMsg);
    errStream << SymExpected.takeError();
    flow_wing::cli::Reporter::error(
        "Entry point not found: " +
        std::string(flow_wing::ir_gen::constants::functions::kMain_fn) + ". " +
        errMsg);
    return ReturnStatus::kFailure;
  }

  // Cast the address to a function pointer
  // Assuming main signature is int main(int argc, char** argv)
  // Adjust signature based on your language spec
  auto MainFn = SymExpected->toPtr<int (*)(int, char **)>();

  try {
    // Setup Fake Args
    int argc = 1;
    char *argv[] = {(char *)"flow-wing-jit", nullptr};

    DEBUG_LOG(" [INFO]: Running JIT Code...", "");

    // EXECUTE
    [[maybe_unused]] int result = MainFn(argc, argv);

    DEBUG_LOG(" [INFO]: JIT Execution finished with code: ", result);

  } catch (const std::exception &e) {
    std::cerr << "Runtime Exception: " << e.what() << std::endl;
  }

  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
