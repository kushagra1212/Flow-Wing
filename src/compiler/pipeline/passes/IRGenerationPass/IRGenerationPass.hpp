
#pragma once

#include "src/compiler/pipeline/ICompilationPass.h"

namespace flow_wing {

namespace compiler {
namespace pipeline {
class IRGenerationPass : public ICompilationPass {
public:
  std::string getName() const override;
  ReturnStatus run(CompilationContext &context) override;
};
} // namespace pipeline
} // namespace compiler

} // namespace flow_wing
