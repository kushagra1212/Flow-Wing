
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
  ExpressionStatement,
  BlockStatement,
  VariableDeclaration,
  IfStatement,
  WhileStatement,
  ForStatement

};
extern std::map<SyntaxKind, std::string> enum_to_string_map;
bool isInt32(const std::string &str);

bool isInt64(const std::string &str);

bool isDouble(const std::string &str);

void init_enum_to_string_map();
} // namespace SyntaxKindUtils

#endif // SYNTAXKINDUTILS_H