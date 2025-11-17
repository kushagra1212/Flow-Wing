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

#include "src/compiler/CompilationContext/CompilationContext.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace flow_wing {
namespace syntax {
class SyntaxToken;

}
namespace lexer {

class TokenReader;
class TokenReaderFactory;

class SourceTokenizer {
public:
  SourceTokenizer(flow_wing::CompilationContext &context);
  std::unique_ptr<syntax::SyntaxToken> nextToken();

  char currentChar() const;
  void advancePosition();
  void advanceLine();
  char peek(const int64_t &offset) const;

  // Error Reporting
  void
  reportError(flow_wing::diagnostic::DiagnosticCode code,
              const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
              const flow_wing::diagnostic::SourceLocation &location);

  // Getters
  const std::string &getLine(const size_t &lineNumber) const {
    return m_context.getSourceLines()[lineNumber];
  }

  size_t position() const { return m_position; }
  size_t lineNumber() const { return m_line_number; }

  // Checkers
  bool isEOLorEOF() const { return isEOL() || isEOF(); }
  bool isEOF() const { return currentChar() == kEndOfFile; }
  bool isEOL() const { return currentChar() == kEndOfLine; }

private:
  std::unique_ptr<syntax::SyntaxToken> nextRawToken();

  const char kEndOfFile = '\0';
  const char kEndOfLine = '\n';
  size_t m_line_number;
  size_t m_position;
  flow_wing::CompilationContext &m_context;
};

} // namespace lexer
} // namespace flow_wing