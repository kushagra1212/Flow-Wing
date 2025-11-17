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

#include "SyntaxToken.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"

namespace flow_wing {
namespace syntax {

SyntaxToken::SyntaxToken(
    const lexer::TokenKind kind, const std::string &text, const std::any value,
    const flow_wing::diagnostic::SourceLocation &source_location,
    std::vector<std::unique_ptr<syntax::SyntaxToken>> leading_tokens)
    : SyntaxNode(source_location), m_token_kind(kind), m_text(text),
      m_value(std::move(value)), m_leading_tokens(std::move(leading_tokens)) {}

// Overrides

void SyntaxToken::accept(visitor::ASTVisitor *visitor) { visitor->visit(this); }

const std::vector<const SyntaxNode *> &SyntaxToken::getChildren() const {
  // Created only once and shared by all SyntaxToken(leaf), to avoid unnecessary
  // memory allocation.
  static const std::vector<const SyntaxNode *> kEmptyChildren;
  return kEmptyChildren;
}

NodeKind SyntaxToken::getKind() const { return NodeKind::kTokenNode; }

} // namespace syntax
} // namespace flow_wing