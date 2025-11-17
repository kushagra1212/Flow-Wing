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

#include "ParserContext.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/compiler/diagnostics/DiagnosticFactory.h"
#include "src/syntax/SyntaxToken.h"
#include <cstddef>
namespace flow_wing {
namespace parser {

ParserContext::ParserContext(CompilationContext &context)
    : m_context(context) {}

const syntax::SyntaxToken *ParserContext::peek(const int &offset) {
  size_t index = m_position + static_cast<size_t>(offset);
  const size_t tokens_size = m_context.getTokens().size();
  if (index >= tokens_size) {
    return m_context.getTokens()[tokens_size - 1].get();
  }
  return m_context.getTokens()[index].get();
}

const syntax::SyntaxToken *ParserContext::getCurrent() { return peek(0); }

const syntax::SyntaxToken *ParserContext::nextToken() {
  auto token = getCurrent();
  if (m_position != m_context.getTokens().size()) {
    m_position++;
  }
  return token;
}

lexer::TokenKind ParserContext::getCurrentTokenKind() {
  return getCurrent()->getTokenKind();
}

void ParserContext::reportError(
    flow_wing::diagnostic::DiagnosticCode code,
    const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
    const flow_wing::diagnostic::SourceLocation &location) {

  m_context.getDiagnostics()->report(
      flow_wing::diagnostic::DiagnosticFactory::create(
          code, args, location, flow_wing::diagnostic::DiagnosticLevel::kError,
          flow_wing::diagnostic::DiagnosticType::kSyntactic));
}

const syntax::SyntaxToken *ParserContext::match(const lexer::TokenKind &kind) {

  const auto current_token_kind = getCurrentTokenKind();

  if (current_token_kind != kind) {
    reportError(flow_wing::diagnostic::DiagnosticCode::kUnexpectedToken,
                {lexer::toString(current_token_kind), lexer::toString(kind)},
                getCurrent()->getSourceLocation());
  }

  return nextToken();
}

const syntax::SyntaxToken *
ParserContext::matchIf(const lexer::TokenKind &kind) {
  if (getCurrentTokenKind() == kind) {
    return match(kind);
  }
  return nullptr;
}

} // namespace parser
} // namespace flow_wing