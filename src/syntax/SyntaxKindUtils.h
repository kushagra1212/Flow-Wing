/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */



#ifndef SYNTAXKINDUTILS_H
#define SYNTAXKINDUTILS_H
#include "../common/Common.h"
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
  QuestionToken,
  GreaterOrEqualsToken,
  GreaterToken,
  SemiColonToken,
  ColonToken,
  CommaToken,
  EndOfLineToken,
  SlashHashToken,
  HashSlashToken,
  HashToken,
  NthgKeyword,
  Int32Keyword,
  Int64Keyword,
  Int8Keyword,
  DeciKeyword,
  Deci32Keyword,
  StrKeyword,
  BoolKeyword,
  BringKeyword,
  SlashSlashToken,
  DotToken,
  AssignmentToken,

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
  OpenBracketToken,
  CloseBracketToken,
  // Strings

  StringToken,
  CharacterToken,

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
  ReturnKeyword,
  OrKeyword,
  ExposeKeyword,
  FromKeyword,
  ElseClause,
  FillKeyword,
  TypeKeyword,
  DeclKeyword,
  NewKeyword,
  ClassKeyword,
  InOutKeyword,
  ExtendsKeyword,
  AsKeyword,
  SwitchKeyword,
  CaseKeyword,
  DefaultKeyword,
  ModuleKeyword,
  NirastKeyword,

  // Identifiers
  IdentifierToken,

  // Experssions

  LiteralExpression,
  UnaryExpression,
  BinaryExpression,
  ParenthesizedExpression,
  AssignmentExpression,
  CompilationUnit,
  CallExpression,
  IndexExpression,
  ContainerExpression,
  NirastExpression,
  FillExpression,
  BracketedExpression,
  MultipleAssignmentExpression,

  // Statements
  GlobalStatement,
  ExpressionStatement,
  CustomTypeStatement,
  BlockStatement,
  VariableDeclaration,
  MultipleVariableDeclaration,
  ClassStatement,
  IfStatement,
  OrIfStatement,
  WhileStatement,
  ForStatement,
  ReturnStatement,
  CommentStatement,
  FunctionDeclarationSyntax,
  ParameterSyntax,
  ArrayParameterSyntax,
  EmptyStatement,
  BringStatementSyntax,
  ContainerStatement,
  CaseStatementSyntax,
  VariableExpressionSyntax,
  SwitchStatementSyntax,
  TernaryExpression,
  ArrayVariableExpressionSyntax,
  BreakStatement,
  ModuleStatement,
  ContinueStatement,
  PrimitiveTypeExpression,
  ArrayTypeExpression,
  ObjectTypeExpression,
  FunctionTypeExpression,
  ObjectExpression,

  // Types (Tokens) Which are not created by the User
  NBU_ARRAY_TYPE,
  NBU_OBJECT_TYPE,
  NBU_FUNCTION_TYPE,
  NBU_UNKNOWN_TYPE,
};
bool isInt32(const std::string &str);

bool isInt64(const std::string &str);

bool isDouble(const std::string &str);

bool isValidInteger(const std::string &str);

bool isNumberTooLarge(const std::string &str);

const std::string to_string(SyntaxKind kind);

bool isType(SyntaxKind kind);
} // namespace SyntaxKindUtils

#endif // SYNTAXKINDUTILS_H