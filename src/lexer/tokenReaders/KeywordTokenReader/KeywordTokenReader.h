#pragma once

#include "../TokenReader.h"
#include "../TokenReaderData.h"

class KeywordTokenReader : public TokenReader {

public:
  std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) override;
};