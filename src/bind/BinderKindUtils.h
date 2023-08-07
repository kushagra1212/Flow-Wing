#pragma once

#include "../Common.h"
namespace BinderKindUtils {
enum BoundNodeKind {
  UnaryExpression,
  BinaryExpression,
  LiteralExpression,
  ParenthesizedExpression,
  AssignmentExpression,
  VariableExpression,
  CallExpression,

  // Statements
  BoundStatementKind,
  ExpressionStatement,
  BlockStatement,
  IfStatement,
  WhileStatement,
  ForStatement,
  BreakStatement,
  ContinueStatement,

  // declarations

  VariableDeclaration,
  FunctionDeclaration
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
};
std::string to_string(BoundNodeKind kind);

std::string to_string(BoundUnaryOperatorKind kind);

std::string to_string(BoundBinaryOperatorKind kind);
} // namespace BinderKindUtils
