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

#include "PipelineFactory.hpp"
#include "src/compiler/pipeline/passes/AstJsonDumperPass/AstJsonDumperPass.hpp"
#include "src/compiler/pipeline/passes/IRGenerationPass/IRGenerationPass.hpp"
#include "src/compiler/pipeline/passes/IrDumperPass/IrDumperPass.hpp"
#include "src/compiler/pipeline/passes/LexerPass/LexerPass.h"
#include "src/compiler/pipeline/passes/LinkerPass/LinkerPass.hpp"
#include "src/compiler/pipeline/passes/ObjectEmissionPass/ObjectEmissionPass.hpp"
#include "src/compiler/pipeline/passes/ParsingPass/ParsingPass.h"
#include "src/compiler/pipeline/passes/SemanticAnalysisPass/SemanticAnalysisPass.hpp"
#include "src/compiler/pipeline/passes/SemanticTreeJsonDumperPass/SemanticTreeJsonDumperPass.hpp"
#include "src/compiler/pipeline/passes/SourceLoaderPass.h"
#include "src/compiler/pipeline/passes/TokenJsonDumperPass/TokenJsonDumperPass.hpp"

namespace flow_wing {
namespace compiler {
namespace pipeline {

PipelineFactory::PipelineFactory() { registerPipelines(); }

CompilationPipeline PipelineFactory::build(const CompilerOptions &options) {
  CompilationPipeline pipeline;

  const PassList &pass_creators = m_pipeline_definitions[options.output_type];
  for (const auto &createPass : pass_creators) {
    pipeline.addPass(createPass());
  }
  return pipeline;
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

  current_passes.push_back([] { return std::make_unique<IRGenerationPass>(); });

  m_pipeline_definitions[CompilerOptions::OutputType::kLLVM_IR] =
      current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kLLVM_IR].push_back(
      [] { return std::make_unique<IrDumperPass>(); });

  m_pipeline_definitions[CompilerOptions::OutputType::kObj] = current_passes;
  m_pipeline_definitions[CompilerOptions::OutputType::kObj].push_back(
      [] { return std::make_unique<ObjectEmissionPass>(); });

  // Add optimization passes here as needed:
  // pipeline.addPass(std::make_unique<SimpleConstantFoldingPass>());

  m_pipeline_definitions[CompilerOptions::OutputType::kExe] =
      m_pipeline_definitions[CompilerOptions::OutputType::kObj];
  m_pipeline_definitions[CompilerOptions::OutputType::kExe].push_back(
      [] { return std::make_unique<LinkerPass>(); });
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing