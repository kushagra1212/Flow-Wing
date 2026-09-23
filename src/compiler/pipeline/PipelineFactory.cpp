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

#include "PipelineFactory.hpp"
#include "src/compiler/pipeline/passes/AstJsonDumperPass/AstJsonDumperPass.hpp"
#include "src/compiler/pipeline/passes/CleanupPass/CleanupPass.hpp"
#include "src/compiler/pipeline/passes/LexerPass/LexerPass.h"
// FLOWWING_FRONTEND_ONLY: the browser build of the lexer, parser and semantic
// analysis (scripts/wasm/build-frontend.sh), which has no LLVM. Everything
// from IR generation on is left out of it; the command line refuses to ask
// for it.
#if !defined(FLOWWING_FRONTEND_ONLY)
#include "src/compiler/pipeline/backends/TargetBackend.hpp"
#include "src/compiler/pipeline/passes/IRGenerationPass/IRGenerationPass.hpp"
#include "src/compiler/pipeline/passes/IrDumperPass/IrDumperPass.hpp"
#include "src/compiler/pipeline/passes/JITCompilerPass/JITCompilerPass.hpp"
#include "src/compiler/pipeline/passes/OptimizationPass/OptimizationPass.hpp"
#endif
#include "src/compiler/pipeline/passes/ParsingPass/ParsingPass.h"
#include "src/compiler/pipeline/passes/SemanticAnalysisPass/SemanticAnalysisPass.hpp"
#include "src/compiler/pipeline/passes/SemanticTreeJsonDumperPass/SemanticTreeJsonDumperPass.hpp"
#include "src/compiler/pipeline/passes/FormatPass/FormatPass.hpp"
#include "src/compiler/pipeline/passes/SourceLoaderPass.h"
#include "src/compiler/pipeline/passes/TokenJsonDumperPass/TokenJsonDumperPass.hpp"
#include "src/utils/LogConfig.h"

namespace flow_wing {
namespace compiler {
namespace pipeline {

namespace {

void append(PassList &passes, PassList more) {
  for (auto &createPass : more) {
    passes.push_back(std::move(createPass));
  }
}

} // namespace

PipelineFactory::PipelineFactory() { registerPipelines(); }

CompilationPipeline PipelineFactory::build(const CompilerOptions &options) {
  CompilationPipeline pipeline;

  if (options.format_source != 0 || options.format_print != 0) {
    pipeline.addPass(std::make_unique<SourceLoaderPass>());
    pipeline.addPass(std::make_unique<LexerPass>());
    pipeline.addPass(std::make_unique<ParsingPass>());
    pipeline.addPass(std::make_unique<FormatPass>());
    return pipeline;
  }

  for (const auto &createPass : passesFor(options)) {
    pipeline.addPass(createPass());
  }
  return pipeline;
}

// --emit=obj and --emit=exe are the only output types that depend on the
// target: the same optimized IR, then the target's back end.
PassList PipelineFactory::passesFor(const CompilerOptions &options) const {
  const auto output_type = options.output_type;
  if (output_type != CompilerOptions::OutputType::kObj &&
      output_type != CompilerOptions::OutputType::kExe) {
    return m_pipeline_definitions.at(output_type);
  }

#if defined(FLOWWING_FRONTEND_ONLY)
  return {};
#else
  const auto &backend = TargetBackend::forPlatform(options.target_platform);
  PassList passes = m_optimized_ir_passes;
  append(passes, backend.objectPasses());
  if (output_type == CompilerOptions::OutputType::kExe) {
    append(passes, backend.linkPasses());
    passes.push_back([] { return std::make_unique<CleanupPass>(); });
  }
  return passes;
#endif
}

void PipelineFactory::registerPipelines() {
  PassList current_passes;

  // Stage 0: Source Loading
  current_passes.push_back([] { return std::make_unique<SourceLoaderPass>(); });

  // Stage 1: Lexing
  current_passes.push_back([] { return std::make_unique<LexerPass>(); });

  // Dump tokens to json
  m_pipeline_definitions[CompilerOptions::OutputType::kTokensJson] =
      current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kTokensJson].push_back(
      [] { return std::make_unique<TokenJsonDumperPass>(); });

  // Stage 2: Parsing
  current_passes.push_back([] { return std::make_unique<ParsingPass>(); });

  m_pipeline_definitions[CompilerOptions::OutputType::kAstJson] =
      current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kAstJson].push_back(
      [] { return std::make_unique<AstJsonDumperPass>(); });

  // Stage 3: Semantic Analysis
  current_passes.push_back(
      [] { return std::make_unique<SemanticAnalysisPass>(); });

  m_pipeline_definitions[CompilerOptions::OutputType::kSemJson] =
      current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kSemJson].push_back(
      [] { return std::make_unique<SemanticTreeJsonDumperPass>(); });

#if defined(FLOWWING_FRONTEND_ONLY)
  (void)m_optimized_ir_passes;
#else
  current_passes.push_back([] { return std::make_unique<IRGenerationPass>(); });

  m_pipeline_definitions[CompilerOptions::OutputType::kLLVM_IR] =
      current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kLLVM_IR].push_back(
      [] { return std::make_unique<IrDumperPass>(); });

  // Stage 5: Optimization
  //
  // Pushed onto current_passes AFTER kLLVM_IR is captured above, so `-E ir`
  // keeps showing exactly what IR generation produced, and BEFORE the JIT
  // pipeline below and the object and executable ones in passesFor, so all
  // three optimize.
  //
  // Neither back end optimizes on its own: object emission goes through
  // LLVMTargetMachineEmitToFile and the JIT hands the module straight to ORC.
  // Without this pass `-O2` reached code generation with the same IR as `-O0`
  // and produced byte-identical binaries.
  current_passes.push_back([] { return std::make_unique<OptimizationPass>(); });

  // The object and executable pipelines continue from here in passesFor,
  // with the target's back end.
  m_optimized_ir_passes = current_passes;

  m_pipeline_definitions[CompilerOptions::OutputType::kJIT] = current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kJIT].push_back(
      [] { return std::make_unique<CleanupPass>(); });
  m_pipeline_definitions[CompilerOptions::OutputType::kJIT].push_back(
      [] { return std::make_unique<JITCompilerPass>(); });
  m_pipeline_definitions[CompilerOptions::OutputType::kJIT].push_back(
      [] { return std::make_unique<CleanupPass>(); });
#endif
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing