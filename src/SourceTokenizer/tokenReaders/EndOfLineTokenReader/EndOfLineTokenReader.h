#pragma once

#include "../TokenReader.h"

class EndOfLineTokenReader : public TokenReader {

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};