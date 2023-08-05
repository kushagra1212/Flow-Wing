#include "BinderKindUtils.h"

std::string BinderKindUtils::to_string(BoundNodeKind kind) {
  switch (kind) {
  case UnaryExpression:
    return "UnaryExpression";
  case BinaryExpression:
    return "BinaryExpression";
  case LiteralExpression:
    return "LiteralExpression";
  case ParenthesizedExpression:
    return "ParenthesizedExpression";
  case AssignmentExpression:
    return "AssignmentExpression";
  case VariableExpression:
    return "VariableExpression";
  case CallExpression:
    return "CallExpression";
  case BoundStatementKind:
    return "BoundStatementKind";
  case ExpressionStatement:
    return "ExpressionStatement";
  case BlockStatement:
    return "BlockStatement";
  case IfStatement:
    return "IfStatement";
  case WhileStatement:
    return "WhileStatement";
  case ForStatement:
    return "ForStatement";
  case VariableDeclaration:
    return "VariableDeclaration";
  default:
    return "NotDefined";
  }
}

std::string BinderKindUtils::to_string(BoundUnaryOperatorKind kind) {
  switch (kind) {
  case Identity:
    return "Identity";
  case Negation:
    return "Negation";
  case LogicalNegation:
    return "LogicalNegation";
  case BitwiseNegation:
    return "BitwiseNegation";
  default:
    return "NotDefined";
  }
}

std::string BinderKindUtils::to_string(BoundBinaryOperatorKind kind) {
  switch (kind) {
  case Addition:
    return "Addition";
  case Subtraction:
    return "Subtraction";
  case Multiplication:
    return "Multiplication";
  case Division:
    return "Division";
  case LogicalAnd:
    return "LogicalAnd";
  case LogicalOr:
    return "LogicalOr";
  case Equals:
    return "Equals";
  case NotEquals:
    return "NotEquals";
  case Less:
    return "Less";
  case LessOrEquals:
    return "LessOrEquals";
  case Greater:
    return "Greater";
  case GreaterOrEquals:
    return "GreaterOrEquals";
  case Assignment:
    return "Assignment";
  case BitwiseAnd:
    return "BitwiseAnd";
  case BitwiseOr:
    return "BitwiseOr";
  case BitwiseXor:
    return "BitwiseXor";
  case Modulus:
    return "Modulus";
  default:
    return "NotDefined";
  }
}