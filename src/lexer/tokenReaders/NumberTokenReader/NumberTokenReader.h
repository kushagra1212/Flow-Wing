#pragma once

#include "../TokenReader.h"

class NumberTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>> readDecimal(Lexer &lexer,
                                                     const int &start);

public:
  std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) override;
};