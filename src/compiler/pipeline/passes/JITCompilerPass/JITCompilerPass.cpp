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
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <unordered_set>

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
#include "llvm/Linker/Linker.h"
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
  const auto &brought = context.getBroughtSourcePaths();
  for (size_t i = 0; i < brought.size(); ++i) {
    const std::string &src_path = brought[i];
    CompilerOptions dep_opts;
    dep_opts.input_file_path = src_path;
    dep_opts.output_dir = parent_opts.output_dir;
    dep_opts.optimization_level = parent_opts.optimization_level;
    dep_opts.enable_server = parent_opts.enable_server;
    dep_opts.enable_linker_warnings = parent_opts.enable_linker_warnings;
    dep_opts.emit_brought_dependency_object = 1;

    CompilationContext dep_ctx(dep_opts);
    dep_ctx.setBroughtCtorPriority(static_cast<int>(i));
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

/// IR paths to load in dependency-first order (brought TUs, then primary), then
/// any other .ll/.bc under the temp dir. Matches AOT link order so
/// `llvm.global_ctors` priorities line up; primary uses the same logical path
/// as `saveIRToFile` for the main TU.
/// Deduplicates by canonical path — brought paths and directory scans can refer
/// to the same file with different spellings; loading twice causes duplicate
/// symbol errors from ORC.
std::vector<std::string>
collectOrderedIRFiles(const CompilationContext &context,
                      const std::string &ir_directory_path,
                      const std::string &ir_ext) {
  namespace fs = std::filesystem;
  std::vector<std::string> ordered;
  std::unordered_set<std::string> seen;

  auto canonical_key = [](const std::string &path) -> std::string {
    std::error_code ec;
    fs::path c = fs::canonical(path, ec);
    return ec ? path : c.string();
  };

  auto try_add = [&](const std::string &logical_path) {
    if (logical_path.empty()) {
      return;
    }
    std::string p = flow_wing::ir_gen::jit_utils::getIRFilePath(
        ir_directory_path, logical_path);
    if (!fs::exists(p)) {
      return;
    }
    const std::string key = canonical_key(p);
    if (seen.insert(key).second) {
      ordered.push_back(std::move(p));
    }
  };

  for (const auto &src : context.getBroughtSourcePaths()) {
    try_add(src);
  }
  try_add(context.getOptions().input_file_path);
  if (!fs::exists(flow_wing::ir_gen::jit_utils::getIRFilePath(
          ir_directory_path, context.getOptions().input_file_path))) {
    try_add(context.getAbsoluteSourceFilePath());
  }

  std::vector<std::string> scan_files =
      flow_wing::io::getFiles(ir_directory_path, ir_ext);
  std::sort(scan_files.begin(), scan_files.end());
  for (const auto &path : scan_files) {
    if (!fs::exists(path)) {
      continue;
    }
    const std::string key = canonical_key(path);
    if (seen.insert(key).second) {
      ordered.push_back(path);
    }
  }

  // `directory_iterator` / scan order is unspecified; that made JIT module add
  // order (and thus llvm.global_ctors / top-level statement order) flaky.
  // Reorder to match semantic compile order: brought TUs in
  // `getBroughtSourcePaths()` order, then the primary TU.
  auto rank_of = [&](const std::string &ir_path) -> int {
    const std::string ik = canonical_key(ir_path);
    int idx = 0;
    for (const auto &src : context.getBroughtSourcePaths()) {
      std::string p = flow_wing::ir_gen::jit_utils::getIRFilePath(
          ir_directory_path, src);
      std::error_code ec;
      if (fs::exists(p, ec) && !ec && canonical_key(p) == ik) {
        return idx;
      }
      ++idx;
    }
    const int primary_rank = idx;
    for (const std::string *ms :
         {&context.getOptions().input_file_path,
          &context.getAbsoluteSourceFilePath()}) {
      if (ms->empty()) {
        continue;
      }
      std::string p = flow_wing::ir_gen::jit_utils::getIRFilePath(
          ir_directory_path, *ms);
      std::error_code ec;
      if (fs::exists(p, ec) && !ec && canonical_key(p) == ik) {
        return primary_rank;
      }
    }
    return 1000000;
  };
  std::stable_sort(ordered.begin(), ordered.end(),
                   [&](const std::string &a, const std::string &b) {
                     const int ra = rank_of(a);
                     const int rb = rank_of(b);
                     if (ra != rb) {
                       return ra < rb;
                     }
                     return canonical_key(a) < canonical_key(b);
                   });

  return ordered;
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

  const std::string ir_ext =
      std::string(flow_wing::ir_gen::constants::paths::kIR_files_extension);
  std::vector<std::string> ir_files =
      collectOrderedIRFiles(context, ir_directory_path, ir_ext);

  llvm::SMDiagnostic err;
  std::vector<std::unique_ptr<llvm::Module>> parsed;
  parsed.reserve(ir_files.size());
  for (const std::string &path : ir_files) {
    LINKING_DEBUG_LOG(" [INFO]: Loading Module for JIT: ", path);
    auto module = llvm::parseIRFile(path, err, *TSCtx->getContext());
    if (!module) {
      flow_wing::cli::Reporter::error("Failed to parse IR file: " + path);
      return ReturnStatus::kFailure;
    }
    parsed.push_back(std::move(module));
  }

  if (parsed.empty()) {
    flow_wing::cli::Reporter::error("JIT: no IR modules to load");
    return ReturnStatus::kFailure;
  }

  // Link into one module so `llvm.global_ctors` (and FlowWing brought TU
  // inits) merge like the system linker: ctor priority order is respected.
  // Multiple `addIRModule` calls left ctor execution order flaky across
  // platforms / ORC versions.
  std::unique_ptr<llvm::Module> combined = std::move(parsed[0]);
  for (size_t i = 1; i < parsed.size(); ++i) {
    if (llvm::Linker::linkModules(*combined, std::move(parsed[i]))) {
      flow_wing::cli::Reporter::error(
          "JIT: failed to link IR module " + std::to_string(i));
      return ReturnStatus::kFailure;
    }
  }

  llvm::Error addErr = JIT->addIRModule(
      llvm::orc::ThreadSafeModule(std::move(combined), *TSCtx));
  if (addErr) {
    std::string errMsg;
    llvm::raw_string_ostream errStream(errMsg);
    errStream << addErr;
    flow_wing::cli::Reporter::error("JIT Error adding module: " + errMsg);
    return ReturnStatus::kFailure;
  }

  // Run llvm.global_ctors (e.g. __fw_brought_module_init for brought TUs)
  // before main — native AOT does this via the linker/runtime; ORC does not
  // unless we call LLJIT::initialize.
  if (llvm::Error init_err = JIT->initialize(JIT->getMainJITDylib())) {
    std::string err_msg;
    llvm::raw_string_ostream os(err_msg);
    llvm::logAllUnhandledErrors(std::move(init_err), os, "JIT: ");
    flow_wing::cli::Reporter::error("JIT static initialization failed: " +
                                    err_msg);
    return ReturnStatus::kFailure;
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
