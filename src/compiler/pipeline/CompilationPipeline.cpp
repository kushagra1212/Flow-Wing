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



#include "CompilationPipeline.h"
#include "src/common/cli/CliReporter.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/Serialization/Tokens/TokenJson.hpp"
#include "src/syntax/SyntaxToken.h"
#include "src/utils/LogConfig.h"

#include <fstream>
namespace flow_wing {

namespace compiler {
namespace pipeline {

void CompilationPipeline::addPass(std::unique_ptr<ICompilationPass> pass) {
  m_passes.push_back(std::move(pass));
}

ReturnStatus CompilationPipeline::run(CompilationContext &context) {
  for (const auto &pass : m_passes) {

    DEBUG_LOG("[[Running pass: ", pass->getName() + " ]]");
    if (pass->run(context) == ReturnStatus::kFailure) {
      DEBUG_LOG("Pipeline stopped after failed pass ", pass->getName());
      return ReturnStatus::kFailure;
    }
  }
  return ReturnStatus::kSuccess;
}
} // namespace pipeline
} // namespace compiler

} // namespace flow_wing
