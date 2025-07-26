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

#include "MultiLineCommentTokenReader.h"
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

std::unique_ptr<SyntaxToken<std::any>>
MultiLineCommentTokenReader::readToken(SourceTokenizer &lexer) {
  std::string text = "";
  const size_t &lineN = lexer.lineNumber();
  const size_t &pos = lexer.position() + 1;
  text += lexer.currentChar();
  lexer.advancePosition(); // skip /
  text += lexer.currentChar();
  lexer.advancePosition(); // skip #

  while (!lexer.isEOF() &&
         (lexer.currentChar() != '#' ||
          (lexer.currentChar() == '#' && lexer.peek(1) != '/'))) {
    if (lexer.isEOL()) {
      text += "\n";
      lexer.advanceLine();
    } else {
      text += lexer.currentChar();
      lexer.advancePosition();
    }
  }

  text += lexer.currentChar();
  lexer.advancePosition();
  text += lexer.currentChar();
  lexer.advancePosition();

  if (lexer.isEOL()) {
    text += "\n";
    lexer.advanceLine();
  }
  return std::make_unique<SyntaxToken<std::any>>(
      lexer.diagnosticHandler()->getAbsoluteFilePath(), lineN,
      SyntaxKindUtils::SyntaxKind::CommentStatement, pos, text, nullptr);
}