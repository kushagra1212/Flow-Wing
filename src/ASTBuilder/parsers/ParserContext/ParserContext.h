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
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include <cstdint>
#include <vector>

class SourceTokenizer;

namespace flow_wing {

class CompilationContext;

namespace diagnostic {
class DiagnosticHandler;
enum class DiagnosticCode : int16_t;
struct SourceLocation;
} // namespace diagnostic

namespace syntax {
class SyntaxToken;
}

namespace parser {

class ParserContext {

public:
  ParserContext(CompilationContext &context);

  //? Syntax Token Methods

  const syntax::SyntaxToken *match(const lexer::TokenKind &kind);
  const syntax::SyntaxToken *matchIf(const lexer::TokenKind &kind);
  const syntax::SyntaxToken *peek(const int &offset);
  lexer::TokenKind getCurrentTokenKind();
  const syntax::SyntaxToken *getCurrent();
  const syntax::SyntaxToken *nextToken();
  CompilationContext &getCompilationContext();

  //? Error Reporting
  void
  reportError(flow_wing::diagnostic::DiagnosticCode code,
              const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
              const flow_wing::diagnostic::SourceLocation &location);

private:
  CompilationContext &m_context;
  size_t m_position = 0;
};
} // namespace parser

} // namespace flow_wing
