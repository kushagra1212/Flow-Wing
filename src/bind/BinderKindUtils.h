#pragma once
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

  // declarations

  VariableDeclaration
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
} // namespace BinderKindUtils
