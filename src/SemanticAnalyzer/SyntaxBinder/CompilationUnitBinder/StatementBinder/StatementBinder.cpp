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

#include "StatementBinder.hpp"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"
#include "src/syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.hpp"
#include "src/syntax/statements/FunctionStatementSyntax/FunctionStatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>

namespace flow_wing {
namespace binding {

StatementBinder::StatementBinder(BinderContext *context,
                                 ExpressionBinder *expression_binder)
    : m_context(context), m_expression_binder(expression_binder) {}

std::unique_ptr<BoundStatement>
StatementBinder::bind(syntax::StatementSyntax *statement) {
  switch (statement->getKind()) {
  case syntax::NodeKind::kBlockStatement:
    return bindBlockStatement(
        static_cast<syntax::BlockStatementSyntax *>(statement));
  case syntax::NodeKind::kFunctionStatement:
    return bindFunctionStatement(
        static_cast<syntax::FunctionStatementSyntax *>(statement));
  case syntax::NodeKind::kCustomTypeStatement:
    return bindCustomTypeStatement(
        static_cast<syntax::CustomTypeStatementSyntax *>(statement));
  case syntax::NodeKind::kVariableDeclaration:
    return bindVariableDeclaration(
        static_cast<syntax::VariableDeclarationSyntax *>(statement));
  case syntax::NodeKind::kExposeStatement:
    return bindExposeStatement(
        static_cast<syntax::ExposeStatementSyntax *>(statement));

  default:
    return bindExpressionStatement(
        static_cast<syntax::ExpressionStatementSyntax *>(statement));
  }
}
} // namespace binding
} // namespace flow_wing