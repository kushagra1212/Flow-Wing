#pragma once

#include "CompilationPipeline.h"
#include "src/compiler/CompilerOptions/CompilerOptions.h"
#include "src/compiler/pipeline/ICompilationPass.h"
#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace flow_wing {
namespace compiler {
namespace pipeline {

class PipelineFactory {
public:
  PipelineFactory();

  CompilationPipeline build(const CompilerOptions &options);

private:
  using PassCreator = std::function<std::unique_ptr<ICompilationPass>()>;
  using PassList = std::vector<PassCreator>;

  std::map<CompilerOptions::OutputType, PassList> m_pipeline_definitions;

  void registerPipelines();
};
} // namespace pipeline
} // namespace compiler
} // namespace flow_wing