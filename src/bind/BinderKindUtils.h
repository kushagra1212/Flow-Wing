#pragma once
namespace BinderKindUtils {
enum BoundNodeKind {
  UnaryExpression,
  BinaryExpression,
  LiteralExpression,
  ParenthesizedExpression,
  AssignmentExpression,
  VariableExpression,

  // Statements
  BoundStatementKind,
  ExpressionStatement,
  BlockStatement,
  IfStatement,

  // declarations

  VariableDeclaration
};

enum BoundUnaryOperatorKind {
  Identity,
  Negation,
  LogicalNegation,
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
} // namespace BinderKindUtils
