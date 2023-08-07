
#ifndef SYNTAXKINDUTILS_H
#define SYNTAXKINDUTILS_H
#include "../Common.h"
namespace SyntaxKindUtils {
enum SyntaxKind {

  // Tokens

  NumberToken,
  WhitespaceToken,
  PlusToken,
  MinusToken,
  StarToken,
  SlashToken,
  OpenParenthesisToken,
  CloseParenthesisToken,
  BadToken,
  EndOfFileToken,
  AmpersandAmpersandToken,
  PipePipeToken,
  EqualsEqualsToken,
  EqualsToken,
  BangToken,
  BangEqualsToken,
  LessOrEqualsToken,
  LessToken,
  GreaterOrEqualsToken,
  GreaterToken,
  SemiColonToken,
  CommaToken,
  EndOfLineToken,

  // Bitwise

  AmpersandToken,
  PipeToken,
  CaretToken,
  TildeToken,

  // percent
  PercentToken,

  // Braces

  OpenBraceToken,
  CloseBraceToken,

  // Strings

  StringToken,

  SemicolonToken,
  // Keywords
  TrueKeyword,
  FalseKeyword,
  VarKeyword,
  ConstKeyword,
  IfKeyword,
  ElseKeyword,
  WhileKeyword,
  ForKeyword,
  ToKeyword,
  FunctionKeyword,
  ContinueKeyword,
  BreakKeyword,

  ElseClause,

  // Identifiers
  IdentifierToken,

  // Experssions

  LiteralExpression,
  UnaryExpression,
  BinaryExpression,
  ParenthesizedExpression,
  AssignmentExpression,
  VariableExpression,
  CompilationUnit,
  CallExpression,

  // Statements
  GlobalStatement,
  ExpressionStatement,
  BlockStatement,
  VariableDeclaration,
  IfStatement,
  WhileStatement,
  ForStatement,

  FunctionDeclarationSyntax,

  ParameterSyntax

};
bool isInt32(const std::string &str);

bool isInt64(const std::string &str);

bool isDouble(const std::string &str);

std::string to_string(SyntaxKind kind);
} // namespace SyntaxKindUtils

#endif // SYNTAXKINDUTILS_H