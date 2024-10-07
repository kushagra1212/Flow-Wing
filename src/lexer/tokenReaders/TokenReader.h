#pragma once

#include "../../syntax/SyntaxToken.h"
#include "../Lexer.h"

class TokenReader {
public:
  virtual ~TokenReader() = default;
  virtual std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) = 0;
};
