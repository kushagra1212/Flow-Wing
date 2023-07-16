#ifndef LEXER_H
#define LEXER_H

#include "../syntax/SyntaxToken.h"
#include "Common.h"

class Lexer {

private:
  std::string text;

private:
  int position;

public:
  std::vector<std::string> logs;

public:
  Lexer(std::string text);

private:
  char getCurrent();

private:
  void next();

public:
  SyntaxToken<std::any> *nextToken();

private:
  SyntaxToken<std::any> *readString();
};
#endif // LEXER_H