#pragma once

#include "../TokenReader.h"

class CharacterTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>>
  unTerminatedCharacterToken(Lexer &lexer, const size_t &start);

  std::unique_ptr<SyntaxToken<std::any>>
  badEscapeSequenceToken(Lexer &lexer, const size_t &start);

public:
  std::unique_ptr<SyntaxToken<std::any>> readToken(Lexer &lexer) override;
};