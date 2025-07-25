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


#include "TokenReaderFactory.h"

#include "CharacterTokenReader/CharacterTokenReader.h"
#include "EndOfFileTokenReader/EndOfFileTokenReader.h"
#include "EndOfLineTokenReader/EndOfLineTokenReader.h"
#include "KeywordTokenReader/KeywordTokenReader.h"
#include "MultiLineCommentTokenReader/MultiLineCommentTokenReader.h"
#include "NumberTokenReader/NumberTokenReader.h"
#include "SingleLineCommentTokenReader/SingleLineCommentTokenReader.h"
#include "StringTokenReader/StringTokenReader.h"
#include "SymbolTokenReader/SymbolTokenReader.h"
#include "TemplateStringTokenReader/TemplateStringTokenReader.h"
#include "TokenReader.h"
#include "WhiteSpaceTokenReader/WhiteSpaceTokenReader.h"

std::unique_ptr<TokenReader>
TokenReaderFactory::createTokenReader(const SourceTokenizer &lexer) {
  if (lexer.isEOF())
    return std::make_unique<EndOfFileTokenReader>();

  if (lexer.isEOL() || lexer.currentChar() == '\n')
    return std::make_unique<EndOfLineTokenReader>();

  if (isspace(lexer.currentChar()))
    return std::make_unique<WhiteSpaceTokenReader>();

  if (isdigit(lexer.currentChar()))
    return std::make_unique<NumberTokenReader>();

  if (isalpha(lexer.currentChar()))
    return std::make_unique<KeywordTokenReader>();

  if (lexer.currentChar() == '\'')
    return std::make_unique<CharacterTokenReader>();

  if (lexer.currentChar() == '"')
    return std::make_unique<StringTokenReader>();

  if (lexer.currentChar() == '`')
    return std::make_unique<TemplateStringTokenReader>();

  if (lexer.currentChar() == '/' && lexer.peek(1) == ';')
    return std::make_unique<SingleLineCommentTokenReader>();

  if (lexer.currentChar() == '/' && lexer.peek(1) == '#')
    return std::make_unique<MultiLineCommentTokenReader>();

  return std::make_unique<SymbolTokenReader>();
}