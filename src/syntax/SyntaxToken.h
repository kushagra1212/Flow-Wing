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

#pragma once

#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxNode.h"
#include <any>
#include <memory>

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
  /** True if any leading token (e.g. before this token) is EndOfLine. */
  bool hasLeadingEndOfLine() const;

  /// Trivia (whitespace, comments) attached before this token in source order.
  const std::vector<std::unique_ptr<syntax::SyntaxToken>> &
  getLeadingTrivia() const {
    return m_leading_tokens;
  }

  /// Trivia attached *after* this token on the same source line — i.e. an
  /// end-of-line comment, which refers to the code before it rather than the
  /// code after it. Only comments land here; the newline that ends the line
  /// stays in the next token's leading trivia, because both the parser
  /// (`hasLeadingEndOfLine`) and the formatter's newline rules are phrased in
  /// terms of the token a newline precedes.
  const std::vector<std::unique_ptr<syntax::SyntaxToken>> &
  getTrailingTrivia() const {
    return m_trailing_tokens;
  }

  void addTrailingTrivia(std::unique_ptr<syntax::SyntaxToken> trivia) {
    m_trailing_tokens.push_back(std::move(trivia));
  }

private:
  lexer::TokenKind m_token_kind;
  std::string m_text;
  std::any m_value;
  std::vector<std::unique_ptr<syntax::SyntaxToken>> m_leading_tokens;
  std::vector<std::unique_ptr<syntax::SyntaxToken>> m_trailing_tokens;
};

} // namespace syntax
} // namespace flow_wing