#pragma once

#include "../../syntax/SyntaxToken.h"
#include "../SourceTokenizer.h"

class TokenReader {
public:
  virtual ~TokenReader() = default;
  virtual std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) = 0;
};
