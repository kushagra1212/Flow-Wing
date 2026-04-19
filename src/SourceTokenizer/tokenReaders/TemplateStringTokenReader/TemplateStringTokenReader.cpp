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

#include "TemplateStringTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace lexer {

std::unique_ptr<syntax::SyntaxToken>
TemplateStringTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();
  std::string text = "", valueText = "";
  text += lexer.currentChar();
  lexer.advancePosition();

  while (!lexer.isEOF() && lexer.currentChar() != '`') {

    if (lexer.isEOL()) {
      text += "\n";
      valueText += "\n";
      lexer.advanceLine();
    } else {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
      lexer.advancePosition();
    }
  }

  if (lexer.currentChar() != '`') {
    return unTerminatedTemplateStringToken(lexer, text, start);
  }

  text += lexer.currentChar();
  lexer.advancePosition();

  return std::make_unique<syntax::SyntaxToken>(
      TokenKind::kTemplateStringLiteralToken, text, valueText,
      diagnostic::SourceLocation(lexer.lineNumber(), start, text.size()));
}

std::unique_ptr<syntax::SyntaxToken>
TemplateStringTokenReader::unTerminatedTemplateStringToken(
    SourceTokenizer &lexer, const std::string &text, const size_t &start) {
  std::unique_ptr<syntax::SyntaxToken> un_terminated_token =
      std::make_unique<syntax::SyntaxToken>(
          TokenKind::kBadToken, text, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start, text.size()));

  lexer.reportError(
      flow_wing::diagnostic::DiagnosticCode::kUnterminatedTemplateStringLiteral,
      {}, un_terminated_token->getSourceLocation());

  return un_terminated_token;
}
} // namespace lexer
} // namespace flow_wing