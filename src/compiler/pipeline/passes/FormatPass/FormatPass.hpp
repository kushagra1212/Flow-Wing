/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */
#pragma once

#include "src/compiler/pipeline/ICompilationPass.h"

namespace flow_wing {
namespace compiler {
namespace pipeline {

class FormatPass : public ICompilationPass {
public:
  std::string getName() const override;
  ReturnStatus run(CompilationContext &context) override;
};

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
