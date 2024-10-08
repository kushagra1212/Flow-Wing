#pragma once

#include "../TokenReader.h"

class NumberTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>> readDecimal(SourceTokenizer &lexer,
                                                     const int &start);

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};