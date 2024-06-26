#pragma once

#include "../Common.h"
#include "../syntax/SyntaxKindUtils.h"

namespace BinderKindUtils {
enum BoundNodeKind {
  UnaryExpression,
  BinaryExpression,
  LiteralExpression,
  ParenthesizedExpression,
  AssignmentExpression,
  VariableExpression,
  CallExpression,
  IndexExpression,
  BoundContainerExpression,
  BoundFillExpression,
  BoundBracketedExpression,
  ArrayVariableExpression,
  BoundTypeExpression,
  BoundArrayTypeExpression,
  BoundObjectTypeExpression,
  BoundObjectExpression,

  // Statements
  BoundStatementKind,
  ExpressionStatement,
  BlockStatement,
  IfStatement,
  OrIfStatement,
  WhileStatement,
  ForStatement,
  BreakStatement,
  ContinueStatement,
  ReturnStatement,
  BringStatement,
  ContainerStatement,
  CustomTypeStatement,
  ClassStatement,

  // declarations

  VariableDeclaration,
  FunctionDeclaration,

  // Symbols
  BoundFunctionSymbol,
};

enum BoundUnaryOperatorKind {
  Identity,
  Negation,
  LogicalNegation,
  BitwiseNegation,
};

enum BoundBinaryOperatorKind {
  Addition,
  Subtraction,
  Multiplication,
  Division,
  LogicalAnd,
  LogicalOr,
  Equals,
  NotEquals,
  Less,
  LessOrEquals,
  Greater,
  GreaterOrEquals,
  Assignment,
  BitwiseAnd,
  BitwiseOr,
  BitwiseXor,
  Modulus,
  IntegerDivision,
  AssignmentToken
};

enum MemoryKind { Stack, Heap, Global, None };

std::string to_string(MemoryKind kind);

std::string to_string(BoundNodeKind kind);

std::string to_string(BoundUnaryOperatorKind kind);

std::string to_string(BoundBinaryOperatorKind kind);

BoundUnaryOperatorKind getUnaryOperatorKind(SyntaxKindUtils::SyntaxKind kind);

BoundBinaryOperatorKind getBinaryOperatorKind(SyntaxKindUtils::SyntaxKind kind);

} // namespace BinderKindUtils
