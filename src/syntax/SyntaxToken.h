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

#pragma once

#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxNode.h"
#include <any>

namespace flow_wing {
namespace syntax {

class SyntaxToken : public SyntaxNode {

public:
  SyntaxToken(
      const lexer::TokenKind kind, const std::string &text,
      const std::any value,
      const flow_wing::diagnostic::SourceLocation &source_location,
      std::vector<std::unique_ptr<syntax::SyntaxToken>> leading_tokens = {});

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters
  const std::string &getText() const { return m_text; }
  const std::any &getValue() const { return m_value; }
  const lexer::TokenKind &getTokenKind() const { return m_token_kind; }

private:
  lexer::TokenKind m_token_kind;
  std::string m_text;
  std::any m_value;
  std::vector<std::unique_ptr<syntax::SyntaxToken>> m_leading_tokens;
};

} // namespace syntax
} // namespace flow_wing