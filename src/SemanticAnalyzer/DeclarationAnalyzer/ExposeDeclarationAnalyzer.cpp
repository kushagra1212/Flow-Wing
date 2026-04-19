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



#include "src/SemanticAnalyzer/DeclarationAnalyzer/DeclarationAnalyzer.hpp"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"

namespace flow_wing {
void analysis::DeclarationAnalyzer::visit(syntax::ExposeStatementSyntax *node) {

  auto *inner = node->getStatement().get();
  switch (inner->getKind()) {
  case syntax::NodeKind::kFunctionStatement:
  case syntax::NodeKind::kClassStatement:
  case syntax::NodeKind::kVariableDeclaration:
  case syntax::NodeKind::kCustomTypeStatement:
    inner->accept(this);
    break;
  default:
    break;
  }
}
} // namespace flow_wing