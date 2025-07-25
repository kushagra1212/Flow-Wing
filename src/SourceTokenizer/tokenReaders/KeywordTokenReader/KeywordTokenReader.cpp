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


#include "KeywordTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
KeywordTokenReader::readToken(SourceTokenizer &lexer) {
  const size_t &start = lexer.position();

  while (!lexer.isEOLorEOF() &&
         (isalnum(lexer.currentChar()) || lexer.currentChar() == '_')) {
    lexer.advancePosition();
  }
  const size_t &length = lexer.position() - start;
  const std::string &text =
      lexer.getLine(lexer.lineNumber()).substr(start, length);

  for (const auto &keyword : __gl_FLOW_WING_KEYWORDS) {

    if (text == keyword._tokenName) {

      if (keyword._tokenType == SyntaxKindUtils::SyntaxKind::TrueKeyword) {
        return std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), keyword._tokenType, start, text, true);
      }

      if (keyword._tokenType == SyntaxKindUtils::SyntaxKind::FalseKeyword) {
        return std::make_unique<SyntaxToken<std::any>>(
            lexer.diagnosticHandler()->getAbsoluteFilePath(),
            lexer.lineNumber(), keyword._tokenType, start, text, false);
      }

      return std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          keyword._tokenType, start, text, text);
    }
  }

  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
      SyntaxKindUtils::SyntaxKind::IdentifierToken, start, text, text);
}
