#include "TokenReaderFactory.h"

#include "CharacterTokenReader/CharacterTokenReader.h"
#include "EndOfFileTokenReader/EndOfFileTokenReader.h"
#include "EndOfLineTokenReader/EndOfLineTokenReader.h"
#include "KeywordTokenReader/KeywordTokenReader.h"
#include "MultiLineCommentTokenReader/MultiLineCommentTokenReader.h"
#include "NumberTokenReader/NumberTokenReader.h"
#include "SingleLineCommentTokenReader/SingleLineCommentTokenReader.h"
#include "StringTokenReader/StringTokenReader.h"
#include "SymbolTokenReader/SymbolTokenReader.h"
#include "TemplateStringTokenReader/TemplateStringTokenReader.h"
#include "TokenReader.h"
#include "WhiteSpaceTokenReader/WhiteSpaceTokenReader.h"

std::unique_ptr<TokenReader>
TokenReaderFactory::createTokenReader(const SourceTokenizer &lexer) {
  if (lexer.isEOF())
    return std::make_unique<EndOfFileTokenReader>();

  if (lexer.isEOL() || lexer.currentChar() == '\n')
    return std::make_unique<EndOfLineTokenReader>();

  if (isspace(lexer.currentChar()))
    return std::make_unique<WhiteSpaceTokenReader>();

  if (isdigit(lexer.currentChar()))
    return std::make_unique<NumberTokenReader>();

  if (isalpha(lexer.currentChar()))
    return std::make_unique<KeywordTokenReader>();

  if (lexer.currentChar() == '\'')
    return std::make_unique<CharacterTokenReader>();

  if (lexer.currentChar() == '"')
    return std::make_unique<StringTokenReader>();

  if (lexer.currentChar() == '`')
    return std::make_unique<TemplateStringTokenReader>();

  if (lexer.currentChar() == '/' && lexer.peek(1) == ';')
    return std::make_unique<SingleLineCommentTokenReader>();

  if (lexer.currentChar() == '/' && lexer.peek(1) == '#')
    return std::make_unique<MultiLineCommentTokenReader>();

  return std::make_unique<SymbolTokenReader>();
}