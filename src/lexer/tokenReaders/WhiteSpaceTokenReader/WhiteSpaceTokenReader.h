#pragma once

#include "../TokenReader.h"

class WhiteSpaceTokenReader : public TokenReader {

public:
  std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) override;
};