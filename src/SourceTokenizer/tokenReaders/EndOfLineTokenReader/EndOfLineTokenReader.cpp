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


#include "EndOfLineTokenReader.h"

std::unique_ptr<SyntaxToken<std::any>>
EndOfLineTokenReader::readToken(SourceTokenizer &lexer) {
  std::unique_ptr<SyntaxToken<std::any>> endOfLineToken =
      std::make_unique<SyntaxToken<std::any>>(
          lexer.diagnosticHandler()->getAbsoluteFilePath(), lexer.lineNumber(),
          SyntaxKindUtils::SyntaxKind::EndOfLineToken, lexer.position(), "", 0);

  if (lexer.currentChar() == '\n')
    lexer.advancePosition();
  else
    lexer.advanceLine();

  return (endOfLineToken);
}