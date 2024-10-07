#pragma once

#include <memory>

class TokenReader;
class Lexer;

class TokenReaderFactory {
public:
  static std::unique_ptr<TokenReader> createTokenReader(const Lexer &lexer);
};