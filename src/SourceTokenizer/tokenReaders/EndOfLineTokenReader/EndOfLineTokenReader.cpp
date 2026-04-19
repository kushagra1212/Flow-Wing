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
#include "src/SourceTokenizer/SourceTokenizer.h"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace lexer {

std::unique_ptr<syntax::SyntaxToken>
EndOfLineTokenReader::readToken(SourceTokenizer &lexer) {

  lexer.advanceLine();

  return std::make_unique<syntax::SyntaxToken>(
      lexer::TokenKind::kEndOfLineToken, "\n", std::any(),
      diagnostic::SourceLocation(lexer.lineNumber(), lexer.position(), 1));
  ;
}
} // namespace lexer
} // namespace flow_wing