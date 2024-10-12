#pragma once

#include "../TokenReader.h"

class TemplateStringTokenReader : public TokenReader {

  std::unique_ptr<SyntaxToken<std::any>>
  unTerminatedTemplateStringToken(SourceTokenizer &lexer, const size_t &start);

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};