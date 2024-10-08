#pragma once

#include "../TokenReader.h"

class CharacterTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>>
  unTerminatedCharacterToken(SourceTokenizer &lexer, const size_t &start);

  std::unique_ptr<SyntaxToken<std::any>>
  badEscapeSequenceToken(SourceTokenizer &lexer, const size_t &start);

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};