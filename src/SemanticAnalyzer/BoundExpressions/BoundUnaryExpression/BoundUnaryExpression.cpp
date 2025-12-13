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

#include "BoundUnaryExpression.hpp"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"

namespace flow_wing {
namespace binding {

BoundUnaryExpression::BoundUnaryExpression(
    lexer::TokenKind operator_token_kind,
    std::unique_ptr<BoundExpression> expression,
    std::shared_ptr<types::Type> type,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_expression(std::move(expression)),
      m_type(type), m_operator_token_kind(operator_token_kind) {}

NodeKind BoundUnaryExpression::getKind() const {
  return NodeKind::kUnaryExpression;
}

void BoundUnaryExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundUnaryExpression::getType() const {
  return m_type;
}

const std::unique_ptr<BoundExpression> &BoundUnaryExpression::getExpression() {
  return m_expression;
}

lexer::TokenKind BoundUnaryExpression::getOperatorTokenKind() {
  return m_operator_token_kind;
}

} // namespace binding
} // namespace flow_wing