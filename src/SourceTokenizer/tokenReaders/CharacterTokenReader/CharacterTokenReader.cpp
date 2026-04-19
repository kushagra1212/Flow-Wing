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

#include "CharacterTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxToken.h"
namespace flow_wing {
namespace lexer {

std::unique_ptr<syntax::SyntaxToken>
CharacterTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start_pos = lexer.position();
  std::string text = "";
  uint32_t value_char = 0;
  text += lexer.currentChar();
  lexer.advancePosition(); // consume the '

  if (lexer.isEOLorEOF()) {
    return unTerminatedCharacterToken(lexer, text, start_pos);
  }

  if (lexer.currentChar() == '\\') {
    text += lexer.currentChar();
    lexer.advancePosition();
    text += lexer.currentChar();
    switch (lexer.currentChar()) {
    case '\'':
      value_char = '\'';
      break;
    case '\\':
      value_char = '\\';
      break;
    case 'n':
      value_char = '\n';
      break;
    case 'r':
      value_char = '\r';
      break;
    case 't':
      value_char = '\t';
      break;
    case '0':
      value_char = '\0';
      break;
      break;
    default: {
      return badEscapeSequenceToken(lexer, std::string(1, lexer.currentChar()),
                                    start_pos);
    }
    }
    lexer.advancePosition();
  } else {
    unsigned char firstByte = (unsigned char)lexer.currentChar();
    int8_t length = 0;

    // 1. Determine length based on UTF-8 header bits
    if ((firstByte & 0x80) == 0) { // 0xxxxxxx (ASCII)
      length = 1;
      value_char = firstByte;
    } else if ((firstByte & 0xE0) == 0xC0) { // 110xxxxx (2 bytes)
      length = 2;
      value_char = firstByte & 0x1F;
    } else if ((firstByte & 0xF0) == 0xE0) { // 1110xxxx (3 bytes)
      length = 3;
      value_char = firstByte & 0x0F;
    } else if ((firstByte & 0xF8) == 0xF0) { // 11110xxx (4 bytes)
      length = 4;
      value_char = firstByte & 0x07;
    } else {
      // Invalid UTF-8 start byte
      return badCharToken(lexer, "Invalid UTF-8 sequence", start_pos);
    }

    // 2. Read the first byte
    text += (char)firstByte;
    lexer.advancePosition();

    // 3. Loop to read the remaining continuation bytes (if any)
    for (int8_t i = 1; i < length; ++i) {
      if (lexer.isEOLorEOF())
        return unTerminatedCharacterToken(lexer, text, start_pos);

      unsigned char nextByte = (unsigned char)lexer.currentChar();

      // Continuation bytes must start with 10xxxxxx
      if ((nextByte & 0xC0) != 0x80) {
        return badCharToken(lexer, "Invalid UTF-8 continuation byte",
                            start_pos);
      }

      // Shift 6 bits and add new data
      value_char = (value_char << 6) | (nextByte & 0x3F);

      text += (char)nextByte;
      lexer.advancePosition();
    }
  }

  text += lexer.currentChar();
  if (lexer.currentChar() != '\'') {
    return unTerminatedCharacterToken(lexer, text, start_pos);
  }

  lexer.advancePosition();

  return std::make_unique<syntax::SyntaxToken>(
      TokenKind::kCharacterLiteralToken, text, value_char,
      diagnostic::SourceLocation(lexer.lineNumber(), start_pos, text.length()));
}

std::unique_ptr<syntax::SyntaxToken>
CharacterTokenReader::unTerminatedCharacterToken(SourceTokenizer &lexer,
                                                 const std::string &text,
                                                 const size_t &start_pos) {

  std::unique_ptr<syntax::SyntaxToken> un_terminated_syntax_token =
      std::make_unique<syntax::SyntaxToken>(
          TokenKind::kBadToken, text, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start_pos,
                                     text.size()));

  lexer.reportError(
      flow_wing::diagnostic::DiagnosticCode::kUnterminatedSingleQuote, {},
      un_terminated_syntax_token->getSourceLocation());

  return un_terminated_syntax_token;
}

std::unique_ptr<syntax::SyntaxToken>
CharacterTokenReader::badEscapeSequenceToken(SourceTokenizer &lexer,
                                             const std::string &text,
                                             const size_t &start_pos) {

  std::unique_ptr<syntax::SyntaxToken> bad_syntax_token =
      std::make_unique<syntax::SyntaxToken>(
          TokenKind::kBadToken, text, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start_pos,
                                     text.size()));

  lexer.reportError(
      flow_wing::diagnostic::DiagnosticCode::kBadCharacterEscapeSequence,
      {lexer.getLine(lexer.lineNumber()).substr(lexer.position(), 1)},
      bad_syntax_token->getSourceLocation());

  return bad_syntax_token;
}

std::unique_ptr<syntax::SyntaxToken> CharacterTokenReader::badCharToken(
    SourceTokenizer &lexer, const std::string &text, const size_t &start_pos) {
  std::unique_ptr<syntax::SyntaxToken> bad_syntax_token =
      std::make_unique<syntax::SyntaxToken>(
          TokenKind::kBadToken, text, std::any(),
          diagnostic::SourceLocation(lexer.lineNumber(), start_pos,
                                     text.size()));
  lexer.reportError(flow_wing::diagnostic::DiagnosticCode::kBadCharacterInput,
                    {text}, bad_syntax_token->getSourceLocation());
  return bad_syntax_token;
}
} // namespace lexer
} // namespace flow_wing