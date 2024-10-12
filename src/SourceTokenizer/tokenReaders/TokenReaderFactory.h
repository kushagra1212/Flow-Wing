#pragma once

#include <memory>

class TokenReader;
class SourceTokenizer;

class TokenReaderFactory {
public:
  static std::unique_ptr<TokenReader>
  createTokenReader(const SourceTokenizer &lexer);
};