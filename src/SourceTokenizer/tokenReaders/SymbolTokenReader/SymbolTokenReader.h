#pragma once

#include "../TokenReader.h"
#include "../TokenReaderData.h"
#include <string>

class SymbolTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>>
  badCharacterToken(SourceTokenizer &lexer, const size_t &start);

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};