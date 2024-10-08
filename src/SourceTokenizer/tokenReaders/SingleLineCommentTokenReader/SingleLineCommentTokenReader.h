#pragma once

#include "../EndOfFileTokenReader/EndOfFileTokenReader.h"
#include "../TokenReader.h"

class SingleLineCommentTokenReader : public TokenReader {

public:
  std::unique_ptr<SyntaxToken<std::any>>
  readToken(SourceTokenizer &lexer) override;
};