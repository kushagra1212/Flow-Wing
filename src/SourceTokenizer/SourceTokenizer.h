#pragma once

#include "../common/Common.h"
#include "../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../syntax/SyntaxToken.h"
#include "../utils/Utils.h"
#include "tokenReaders/TokenReaderFactory.h"

class TokenReader;
class TokenReaderFactory;

class SourceTokenizer {
  const char _END_OF_FILE = '\r';
  const char _END_OF_LINE = '\1';
  size_t _lineNumber;
  size_t _position;
  size_t _textSize = 0;

  std::vector<std::string> _sourceCode;
  FlowWing::DiagnosticHandler *_diagnosticHandler;

public:
  std::unique_ptr<SyntaxToken<std::any>> nextToken();
  SourceTokenizer(const std::vector<std::string> &sourceCode,
                  FlowWing::DiagnosticHandler *diagnosticHandler);

  const char currentChar() const;
  void advancePosition();
  void advanceLine();
  const char peek(const int64_t &offset) const;

  const bool isEOLorEOF() const { return isEOL() || isEOF(); }
  const bool isEOF() const { return currentChar() == _END_OF_FILE; }
  const bool isEOL() const { return currentChar() == _END_OF_LINE; }

  const std::string getLine(const size_t &lineNumber) const {
    return _sourceCode[lineNumber];
  }

  const size_t position() const { return _position; }
  const size_t lineNumber() const { return _lineNumber; }
  FlowWing::DiagnosticHandler *diagnosticHandler() {
    return _diagnosticHandler;
  }
};