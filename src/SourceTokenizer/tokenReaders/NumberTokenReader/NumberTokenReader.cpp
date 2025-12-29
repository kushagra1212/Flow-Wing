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

  bool isHex = false;

  // Check for Hex Prefix '0x' or '0X'
  if (lexer.currentChar() == '0') {
    lexer.advancePosition(); // consume '0'
    if (!lexer.isEOLorEOF() &&
        (lexer.currentChar() == 'x' || lexer.currentChar() == 'X')) {
      isHex = true;
      lexer.advancePosition(); // consume 'x'
    }
  }

  if (isHex) {
    // Hex: 0-9, a-f, A-F
    while (!lexer.isEOLorEOF() && isxdigit(lexer.currentChar())) {
      lexer.advancePosition();
    }
  } else {
    while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
      lexer.advancePosition();
    }

    // Check for float/double dot '.'
    if ((lexer.currentChar() == '.' || lexer.currentChar() == 'e' ||
         lexer.currentChar() == 'E')) {
      return readDecimal(lexer, start_pos);
    }
  }

  // Check for int64 suffix 'l'
  bool is_int64 = false;
  if (!lexer.isEOLorEOF() && (lexer.currentChar() == 'l')) {
    lexer.advancePosition();
    is_int64 = true;
  }

  const size_t &length = lexer.position() - start_pos;
  const std::string &text =
      lexer.getLine(line_number).substr(start_pos, length);
  auto location =
      diagnostic::SourceLocation(line_number, start_pos, text.size());

  try {
    int64_t value;
    if (isHex) {
      // Base 16 parsing
      uint64_t u_val = std::stoull(text, nullptr, 16);
      value = static_cast<int64_t>(u_val);
    } else {
      // Base 10 parsing (Your existing logic)
      uint64_t u_val = std::stoull(text);
      if (u_val > 9223372036854775807ULL && u_val != 9223372036854775808ULL) {
        throw std::out_of_range("Overflow");
      }
      value = static_cast<int64_t>(u_val);
    }

    // Use Int64LiteralToken if 'l' suffix was present
    auto token_kind = is_int64 ? lexer::TokenKind::kInt64LiteralToken
                               : lexer::TokenKind::kIntegerLiteralToken;

    return std::make_unique<syntax::SyntaxToken>(token_kind, text, value,
                                                 location);
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

  if (lexer.currentChar() == '.') {
    lexer.advancePosition(); // consume the dot

    while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
      lexer.advancePosition();
    }
  }

  // Check for scientific notation (e.g., 1.5e10, 1.5E-5)
  if (lexer.currentChar() == 'e' || lexer.currentChar() == 'E') {
    lexer.advancePosition(); // consume 'e' or 'E'

    // Optional sign
    if (lexer.currentChar() == '+' || lexer.currentChar() == '-') {
      lexer.advancePosition();
    }

    // Exponent digits
    while (!lexer.isEOLorEOF() && isdigit(lexer.currentChar())) {
      lexer.advancePosition();
    }
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
