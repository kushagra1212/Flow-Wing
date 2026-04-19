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

#include "StringTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace lexer {

std::unique_ptr<syntax::SyntaxToken>
StringTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start_pos = lexer.position();
  std::string text = "", valueText = "";
  text += lexer.currentChar();
  lexer.advancePosition();
  while (!lexer.isEOLorEOF() && lexer.currentChar() != '"') {
    if (lexer.currentChar() == '\\') {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
      lexer.advancePosition();
      text += lexer.currentChar();
      switch (lexer.currentChar()) {
      case '"':
      case '\\':
      case 'n':
      case 'r':
      case 't':
      case '0':
        valueText += lexer.currentChar();
        lexer.advancePosition();
        break;
      default: {
        return badEscapeSequenceToken(
            lexer, std::string(1, lexer.currentChar()), start_pos);
      }
      }
    } else {
      text += lexer.currentChar();
      valueText += lexer.currentChar();
      lexer.advancePosition();
    }
  }

  text += lexer.currentChar();
  if (lexer.currentChar() != '"') {
    return unTerminatedStringToken(lexer, text, start_pos);
  }

  lexer.advancePosition();

  return std::make_unique<syntax::SyntaxToken>(
      lexer::TokenKind::kStringLiteralToken, text, valueText,
      diagnostic::SourceLocation(lexer.lineNumber(), start_pos, text.size()));
}

std::unique_ptr<syntax::SyntaxToken> StringTokenReader::unTerminatedStringToken(
    SourceTokenizer &lexer, const std::string &text, const size_t &start_pos) {

  std::unique_ptr<syntax::SyntaxToken> unterminated_syntax_token =
      std::make_unique<syntax::SyntaxToken>(
          lexer::TokenKind::kBadToken, text, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start_pos,
                                     text.size()));

  lexer.reportError(
      flow_wing::diagnostic::DiagnosticCode::kUnterminatedStringLiteral, {},
      unterminated_syntax_token->getSourceLocation());

  return unterminated_syntax_token;
}

std::unique_ptr<syntax::SyntaxToken> StringTokenReader::badEscapeSequenceToken(
    SourceTokenizer &lexer, const std::string &text, const size_t &start_pos) {

  std::unique_ptr<syntax::SyntaxToken> bad_syntax_token =
      std::make_unique<syntax::SyntaxToken>(
          lexer::TokenKind::kBadToken, text, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start_pos,
                                     text.size()));

  lexer.reportError(flow_wing::diagnostic::DiagnosticCode::
                        kBadCharacterEscapeSequenceInStringLiteral,
                    {text}, bad_syntax_token->getSourceLocation());

  return bad_syntax_token;
}

} // namespace lexer
} // namespace flow_wing