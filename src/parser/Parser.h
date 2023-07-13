#ifndef PARSER_H
#define PARSER_H
#include "../lexer/Lexer.h"
#include "../syntax/CompilationUnitSyntax.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/NumberExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"
class Parser {
private:
  std::vector<SyntaxToken *> tokens;
  int position;

public:
  std::vector<std::string> logs;

public:
  Parser(std::string text);

private:
  SyntaxToken *peek(int offset);

private:
  SyntaxToken *getCurrent();

private:
  SyntaxToken *nextToken();

private:
  SyntaxToken *match(SyntaxKindUtils::SyntaxKind kind);

public:
  CompilationUnitSyntax *parseCompilationUnit();

private:
  ExpressionSyntax *parseExpression(int parentPrecedence = 0);

private:
  ExpressionSyntax *parsePrimaryExpression();
};
#endif