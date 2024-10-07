#pragma once

#include "../TokenReader.h"
#include "../TokenReaderData.h"
#include <string>

class SymbolTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>> badCharacterToken(Lexer &lexer,
                                                           const size_t &start);

public:
  std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) override;
};