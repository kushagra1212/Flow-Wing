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
  case FunctionDeclaration:
    return "FunctionDeclaration";
  case BreakStatement:
    return "BreakStatement";
  case ContinueStatement:
    return "ContinueStatement";
  case ReturnStatement:
    return "ReturnStatement";
  case OrIfStatement:
    return "OrIfStatement";
  case BringStatement:
    return "BringStatement";
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
  case IntegerDivision:
    return "IntegerDivision";
  default:
    return "NotDefined";
  }
}

BinderKindUtils::BoundUnaryOperatorKind
BinderKindUtils::getUnaryOperatorKind(SyntaxKindUtils::SyntaxKind kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::PlusToken:
    return BinderKindUtils::BoundUnaryOperatorKind::Identity;

  case SyntaxKindUtils::SyntaxKind::MinusToken:
    return BinderKindUtils::BoundUnaryOperatorKind::Negation;

  case SyntaxKindUtils::SyntaxKind::BangToken:
    return BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation;

  case SyntaxKindUtils::SyntaxKind::TildeToken:
    return BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation;

  default:
    throw "Unexpected unary operator";
  }
  return BinderKindUtils::BoundUnaryOperatorKind::Identity;
}

BinderKindUtils::BoundBinaryOperatorKind
BinderKindUtils::getBinaryOperatorKind(SyntaxKindUtils::SyntaxKind kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::PlusToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Addition;

  case SyntaxKindUtils::SyntaxKind::MinusToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Subtraction;

  case SyntaxKindUtils::SyntaxKind::StarToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Multiplication;

  case SyntaxKindUtils::SyntaxKind::SlashToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Division;

  case SyntaxKindUtils::SyntaxKind::SlashSlashToken:
    return BinderKindUtils::BoundBinaryOperatorKind::IntegerDivision;

  case SyntaxKindUtils::SyntaxKind::PercentToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Modulus;

  case SyntaxKindUtils::SyntaxKind::EqualsEqualsToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Equals;

  case SyntaxKindUtils::SyntaxKind::BangEqualsToken:
    return BinderKindUtils::BoundBinaryOperatorKind::NotEquals;

  case SyntaxKindUtils::SyntaxKind::AmpersandAmpersandToken:
    return BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd;

  case SyntaxKindUtils::SyntaxKind::PipePipeToken:
    return BinderKindUtils::BoundBinaryOperatorKind::LogicalOr;

  case SyntaxKindUtils::SyntaxKind::LessToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Less;

  case SyntaxKindUtils::SyntaxKind::LessOrEqualsToken:
    return BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals;

  case SyntaxKindUtils::SyntaxKind::GreaterToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Greater;

  case SyntaxKindUtils::SyntaxKind::GreaterOrEqualsToken:
    return BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals;

  case SyntaxKindUtils::SyntaxKind::EqualsToken:
    return BinderKindUtils::BoundBinaryOperatorKind::Assignment;

  case SyntaxKindUtils::SyntaxKind::AmpersandToken:
    return BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd;

  case SyntaxKindUtils::SyntaxKind::PipeToken:
    return BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr;

  case SyntaxKindUtils::SyntaxKind::CaretToken:
    return BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor;

  default:
    throw "Unexpected binary operator";
  }

  return BinderKindUtils::BoundBinaryOperatorKind::Addition;
}