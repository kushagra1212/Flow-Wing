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
#include "src/syntax/expression/ErrorExpressionSyntax/ErrorExpressionSyntax.hpp"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

ErrorExpressionSyntax::ErrorExpressionSyntax(
    const std::vector<const SyntaxToken *> &skipped_tokens,
    flow_wing::diagnostic::Diagnostic diagnostic)
    : m_diagnostic(diagnostic), m_skipped_tokens(skipped_tokens) {}

// Overrides
NodeKind ErrorExpressionSyntax::getKind() const {
  return NodeKind::kErrorExpression;
}

void ErrorExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxToken *> &
ErrorExpressionSyntax::getSkippedTokens() const {
  return m_skipped_tokens;
}

const flow_wing::diagnostic::Diagnostic &
ErrorExpressionSyntax::getDiagnostic() const {
  return m_diagnostic;
}

const std::vector<const SyntaxNode *> &
ErrorExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &token : m_skipped_tokens) {
      if (token) {
        m_children.emplace_back(token);
      }
    }
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing