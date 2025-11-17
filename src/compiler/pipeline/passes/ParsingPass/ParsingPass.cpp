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



#include "ParsingPass.h"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/compiler/CompilationContext/CompilationContext.h"

namespace flow_wing {

namespace compiler {
namespace pipeline {

std::string ParsingPass::getName() const { return "Parsing"; }

ReturnStatus ParsingPass::run(CompilationContext &context) {
  auto &diagnostics = context.getDiagnostics();

  parser::ASTBuilder parser(context);

  auto ast = parser.create();

  if (diagnostics->hasError(diagnostic::DiagnosticType::kLexical) ||
      diagnostics->hasError(diagnostic::DiagnosticType::kSyntactic)) {
    return ReturnStatus::kFailure;
  }

  context.setAst(std::move(ast));

  return ReturnStatus::kSuccess;
}

} // namespace pipeline
} // namespace compiler
} // namespace flow_wing
