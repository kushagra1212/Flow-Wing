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

#include "SourceTokenizer.h"

#include "src/SourceTokenizer/tokenReaders/TokenReaderFactory.h"
#include "src/compiler/diagnostics/DiagnosticFactory.h"
#include "src/syntax/SyntaxToken.h"
#include "tokenReaders/TokenReader.h"
#include <memory>
#include <vector>

namespace flow_wing {
namespace lexer {

SourceTokenizer::SourceTokenizer(flow_wing::CompilationContext &context)
    : m_line_number(0), m_position(0), m_context(context) {}

char SourceTokenizer::currentChar() const { return peek(0); }

char SourceTokenizer::peek(const int64_t &offset) const {
  if (m_line_number >= m_context.getSourceLines().size())
    return kEndOfFile;

  if (m_position + static_cast<size_t>(offset) >=
      m_context.getSourceLines()[m_line_number].length())
    return kEndOfLine;

  return m_context.getSourceLines()[m_line_number]
                                   [m_position + static_cast<size_t>(offset)];
}

void SourceTokenizer::advancePosition() { m_position++; }

void SourceTokenizer::advanceLine() {
  m_line_number++;
  m_position = 0;
}

std::unique_ptr<syntax::SyntaxToken> SourceTokenizer::nextToken() {

  std::vector<std::unique_ptr<syntax::SyntaxToken>> leading_tokens;

  while (true) {
    auto token = nextRawToken();
    if (token->getTokenKind() == lexer::TokenKind::kWhitespaceToken ||
        token->getTokenKind() == lexer::TokenKind::kEndOfLineToken ||
        token->getTokenKind() == lexer::TokenKind::kSingleLineCommentToken ||
        token->getTokenKind() == lexer::TokenKind::kMultiLineCommentToken) {
      leading_tokens.push_back(std::move(token));
    } else {
      return std::make_unique<syntax::SyntaxToken>(
          token->getTokenKind(), token->getText(), token->getValue(),
          token->getSourceLocation(), std::move(leading_tokens));
    }
  }
}

std::unique_ptr<syntax::SyntaxToken> SourceTokenizer::nextRawToken() {
  return TokenReaderFactory::createTokenReader(*this)->readToken(*this);
}

void SourceTokenizer::reportError(
    flow_wing::diagnostic::DiagnosticCode code,
    const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
    const flow_wing::diagnostic::SourceLocation &location) {

  m_context.getDiagnostics()->report(
      flow_wing::diagnostic::DiagnosticFactory::create(
          code, args, location, flow_wing::diagnostic::DiagnosticLevel::kError,
          flow_wing::diagnostic::DiagnosticType::kLexical));
}

} // namespace lexer
} // namespace flow_wing