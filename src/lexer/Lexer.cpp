#include "Lexer.h"

#include "tokenReaders/TokenReader.h"

Lexer::Lexer(const std::vector<std::string> &sourceCode,
             FlowWing::DiagnosticHandler *diagnosticHandler)
    : _sourceCode(sourceCode), _diagnosticHandler(diagnosticHandler),
      _textSize(sourceCode.size()), _position(0), _lineNumber(0) {}

const char Lexer::currentChar() const { return peek(0); }

const char Lexer::peek(const int64_t &offset) const {
  if (_lineNumber >= _textSize)
    return _END_OF_FILE;

  if (_position + offset >= _sourceCode[_lineNumber].length())
    return _END_OF_LINE;

  return _sourceCode[_lineNumber][_position + offset];
}

void Lexer::advancePosition() { _position++; }

void Lexer::advanceLine() {
  _lineNumber++;
  _position = 0;
}

std::unique_ptr<SyntaxToken<std::any>> Lexer::nextToken() {
  return TokenReaderFactory::createTokenReader(*this)->readToken(*this);
}
