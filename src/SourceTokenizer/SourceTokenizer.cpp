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

#include "tokenReaders/TokenReader.h"

SourceTokenizer::SourceTokenizer(const std::vector<std::string> &sourceCode,
                                 FlowWing::DiagnosticHandler *diagnosticHandler)
    : _sourceCode(sourceCode), _diagnosticHandler(diagnosticHandler),
      _textSize(sourceCode.size()), _position(0), _lineNumber(0) {}

const char SourceTokenizer::currentChar() const { return peek(0); }

const char SourceTokenizer::peek(const int64_t &offset) const {
  if (_lineNumber >= _textSize)
    return _END_OF_FILE;

  if (_position + offset >= _sourceCode[_lineNumber].length())
    return _END_OF_LINE;

  return _sourceCode[_lineNumber][_position + offset];
}

void SourceTokenizer::advancePosition() { _position++; }

void SourceTokenizer::advanceLine() {
  _lineNumber++;
  _position = 0;
}

std::unique_ptr<SyntaxToken<std::any>> SourceTokenizer::nextToken() {
  return TokenReaderFactory::createTokenReader(*this)->readToken(*this);
}
