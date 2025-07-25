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


#include "CodeFormatter.h"

#include "../parsers/ParserContext/ParserContext.h"

CodeFormatter::CodeFormatter(ParserContext *parserCtx) : parserCtx(parserCtx) {}

void CodeFormatter::appendNewLine() {
  if (parserCtx->getCurrent() &&
      parserCtx->getKind() != SyntaxKindUtils::SyntaxKind::CommentStatement)
    append(NEW_LINE);
  else
    appendWithSpace();
}

void CodeFormatter::append(const std::string &str) {
  _formattedSourceCode += str;
}
void CodeFormatter::appendWithSpace() { append(ONE_SPACE); }

const std::string &CodeFormatter::getFormattedSourceCode() {
  return _formattedSourceCode;
}

//? Handling Indentation

void CodeFormatter::appendIndentAmount(const std::string &str) {
  _indentAmount += str;
}

void CodeFormatter::setIndentAmount(const std::string &indentAmount) {
  _indentAmount = indentAmount;
}

std::string CodeFormatter::getIndentAmount() { return _indentAmount; }
