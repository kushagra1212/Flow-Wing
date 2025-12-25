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

#include "NumberTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace lexer {

std::unique_ptr<syntax::SyntaxToken>
NumberTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t start_pos = lexer.position();
  const size_t line_number = lexer.lineNumber();

  while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
    lexer.advancePosition();
  }

  //  Detect decimal number
  if (lexer.currentChar() == '.') {
    return readDecimal(lexer, start_pos);
  }

  const size_t &length = lexer.position() - start_pos;
  const std::string &text =
      lexer.getLine(line_number).substr(start_pos, length);
  auto location =
      diagnostic::SourceLocation(line_number, start_pos, text.size());

  try {
    int64_t value = std::stoll(text);
    return std::make_unique<syntax::SyntaxToken>(
        lexer::TokenKind::kIntegerLiteralToken, text, value, location);
  } catch (const std::out_of_range &) {
    lexer.reportError(diagnostic::DiagnosticCode::kNumberTooLargeForInt, {text},
                      location);
    return std::make_unique<syntax::SyntaxToken>(TokenKind::kBadToken, text,
                                                 std::any(), location);
  } catch (const std::invalid_argument &) {
    lexer.reportError(diagnostic::DiagnosticCode::kBadCharacterInput, {text},
                      location);
    return std::make_unique<syntax::SyntaxToken>(TokenKind::kBadToken, text,
                                                 std::any(), location);
  }
}

std::unique_ptr<syntax::SyntaxToken>
NumberTokenReader::readDecimal(SourceTokenizer &lexer,
                               const size_t &start_pos) {
  const size_t line_number = lexer.lineNumber();
  lexer.advancePosition(); // consume the dot

  while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
    lexer.advancePosition();
  }

  int8_t is_deci32 = 0;

  if (lexer.currentChar() == 'f') {
    lexer.advancePosition();
    is_deci32 = 1;
  }

  const size_t &length = lexer.position() - start_pos;
  const std::string &text =
      lexer.getLine(line_number).substr(start_pos, length);
  auto location =
      diagnostic::SourceLocation(line_number, start_pos, text.size());

  try {
    if (is_deci32) {
      float value = std::stof(text);
      return std::make_unique<syntax::SyntaxToken>(
          TokenKind::kFloatLiteralToken, text, value, location);
    } else {
      double value = std::stod(text);
      return std::make_unique<syntax::SyntaxToken>(
          TokenKind::kDoubleLiteralToken, text, value, location);
    }
  } catch (const std::exception &) {
    lexer.reportError(diagnostic::DiagnosticCode::kBadCharacterInput, {text},
                      location);
    return std::make_unique<syntax::SyntaxToken>(TokenKind::kBadToken, text,
                                                 std::any(), location);
  }
}
} // namespace lexer
} // namespace flow_wing
