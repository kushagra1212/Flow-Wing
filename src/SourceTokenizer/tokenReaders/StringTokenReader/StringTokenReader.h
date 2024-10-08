#pragma once

#include "../TokenReader.h"

class StringTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>>
  unTerminatedStringToken(SourceTokenizer &lexer, const size_t &start);

  std::unique_ptr<SyntaxToken<std::any>>
  badEscapeSequenceToken(SourceTokenizer &lexer, const size_t &start);

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};