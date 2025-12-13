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

#include "IRGenerationPass.hpp"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/IRGen/GlobalDeclarationsInitializer/GlobalDeclarationsInitializer.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/utils/LogConfig.h"

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string IRGenerationPass::getName() const { return "IR Generation"; }

ReturnStatus IRGenerationPass::run(CompilationContext &context) {

  auto &diagnostics = context.getDiagnostics();
  if (diagnostics->hasError(diagnostic::DiagnosticType::kSemantic)) {

    CODEGEN_DEBUG_LOG("IR Generation failed due to previous semantic errors.",
                      "IRGenerationPass");
    return ReturnStatus::kFailure;
  }

  ir_gen::IRGenContext ir_gen_context(context);
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
