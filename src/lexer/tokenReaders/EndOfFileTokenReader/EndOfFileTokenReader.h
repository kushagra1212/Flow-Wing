#pragma once

#include "../TokenReader.h"

class EndOfFileTokenReader : public TokenReader {

public:
  std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) override;
};