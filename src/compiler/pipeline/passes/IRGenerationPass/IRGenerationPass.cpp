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

#include "IRGenerationPass.hpp"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/GlobalDeclarationsInitializer/GlobalDeclarationsInitializer.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/IRGen/io/ObjectUtils.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/pipeline/PipelineFactory.hpp"
#include "src/utils/LogConfig.h"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
// clang-format on

namespace flow_wing {

namespace compiler {
namespace pipeline {

namespace {

ReturnStatus compileBroughtSourcesToObjects(CompilationContext &context) {
  const auto &parent_opts = context.getOptions();
  const auto &brought = context.getBroughtSourcePaths();
  for (size_t i = 0; i < brought.size(); ++i) {
    const std::string &src_path = brought[i];
    CompilerOptions dep_opts;
    dep_opts.input_file_path = src_path;
    dep_opts.output_type = CompilerOptions::OutputType::kObj;
    dep_opts.output_dir = parent_opts.output_dir;
    dep_opts.optimization_level = parent_opts.optimization_level;
    // Brought files are compiled for the same machine as the entry. Without
    // this a wasm32 build compiled them natively, for 64-bit pointers.
    dep_opts.target_platform = parent_opts.target_platform;
    dep_opts.enable_server = parent_opts.enable_server;
    dep_opts.enable_linker_warnings = parent_opts.enable_linker_warnings;
    dep_opts.emit_brought_dependency_object = 1;
    dep_opts.progress = ProgressMode::kNever;

    context.getBuildProgress().unit(src_path);

    std::string entry_file_path = parent_opts.input_file_path;
    CompilationContext dep_ctx(dep_opts, entry_file_path);
    dep_ctx.setBroughtCtorPriority(static_cast<int>(i));
    PipelineFactory factory;
    CompilationPipeline pipeline = factory.build(dep_opts);
    if (pipeline.run(dep_ctx) != ReturnStatus::kSuccess) {
      return ReturnStatus::kFailure;
    }
    context.addBroughtObjectFile(
        ir_gen::ObjectUtils::getObjectFilePath(
            dep_ctx.getAbsoluteSourceFilePath(),
            dep_ctx.getOptions().output_dir));
  }
  return ReturnStatus::kSuccess;
}

} // namespace

std::string IRGenerationPass::getName() const { return "IR Generation"; }

ReturnStatus IRGenerationPass::run(CompilationContext &context) {

  auto &diagnostics = context.getDiagnostics();
  if (diagnostics->hasError(diagnostic::DiagnosticType::kSemantic)) {

    CODEGEN_DEBUG_LOG("IR Generation failed due to previous semantic errors.",
                      "IRGenerationPass");
    return ReturnStatus::kFailure;
  }

  // Only the root compiles brought files. A dependency's own pipeline also
  // produces kObj, and used to compile ITS brought files again, recursively:
  // a module brought by 14 files was compiled 15 times. Every repeat produced
  // an identical object, so this was wasted time, not wrong output. The
  // root's list already holds every transitive dependency once,
  // dependency-first, so its loop is complete on its own.
  const auto &opts = context.getOptions();
  const bool builds_object =
      opts.output_type == CompilerOptions::OutputType::kObj ||
      opts.output_type == CompilerOptions::OutputType::kExe;
  if (builds_object && !opts.emit_brought_dependency_object) {
    if (compileBroughtSourcesToObjects(context) != ReturnStatus::kSuccess) {
      return ReturnStatus::kFailure;
    }
    // After the dependencies, as Cargo prints it: the entry is the last unit
    // compiled before the link.
    context.getBuildProgress().unit(context.getAbsoluteSourceFilePath());
  }

  ir_gen::IRGenContext ir_gen_context(context);

  // Definitions for `bring` dependencies live in separate object files produced
  // during semantic analysis; the linker merges them with this TU.

  ir_gen::GlobalDeclarationsInitializer global_declarations_initializer(
      ir_gen_context);
  global_declarations_initializer.initialize();

  if (context.getDiagnostics()->hasError(
          diagnostic::DiagnosticType::kCodeGen)) {
    return ReturnStatus::kFailure;
  }

  ir_gen::IRGenerator ir_generator(ir_gen_context);
  ir_generator.generate();

  if (context.getDiagnostics()->hasError(
          diagnostic::DiagnosticType::kCodeGen)) {
    return ReturnStatus::kFailure;
  }

  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
