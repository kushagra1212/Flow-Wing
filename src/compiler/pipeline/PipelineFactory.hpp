#pragma once

#include "CompilationPipeline.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/pipeline/PassList.hpp"
#include <map>

namespace flow_wing {
namespace compiler {
namespace pipeline {

class PipelineFactory {
public:
  PipelineFactory();

  CompilationPipeline build(const CompilerOptions &options);

private:
  // Output types whose passes are the same for every target.
  std::map<CompilerOptions::OutputType, PassList> m_pipeline_definitions;
  // Source loading through optimization: the start of --emit=obj and
  // --emit=exe, which the target's TargetBackend finishes.
  PassList m_optimized_ir_passes;

  void registerPipelines();
  PassList passesFor(const CompilerOptions &options) const;
};
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
