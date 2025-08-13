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

#include "SourceTokenizer.h"

#include "src/SourceTokenizer/tokenReaders/TokenReaderFactory.h"
#include "src/syntax/SyntaxToken.h"
#include "tokenReaders/TokenReader.h"

SourceTokenizer::SourceTokenizer(const std::vector<std::string> &sourceCode,
                                 FlowWing::DiagnosticHandler *diagnosticHandler)
    : _lineNumber(0), _position(0), _textSize(sourceCode.size()),
      _sourceCode(sourceCode), _diagnosticHandler(diagnosticHandler) {}

char SourceTokenizer::currentChar() const { return peek(0); }

char SourceTokenizer::peek(const int64_t &offset) const {
  if (_lineNumber >= _textSize)
    return _END_OF_FILE;

  if (_position + static_cast<size_t>(offset) >=
      _sourceCode[_lineNumber].length())
    return _END_OF_LINE;

  return _sourceCode[_lineNumber][_position + static_cast<size_t>(offset)];
}

void SourceTokenizer::advancePosition() { _position++; }

void SourceTokenizer::advanceLine() {
  _lineNumber++;
  _position = 0;
}

std::unique_ptr<SyntaxToken<std::any>> SourceTokenizer::nextToken() {
  return TokenReaderFactory::createTokenReader(*this)->readToken(*this);
}
