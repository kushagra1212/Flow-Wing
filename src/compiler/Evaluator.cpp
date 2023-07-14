#include "Evaluator.h"
int Evaluator::evaluate(BoundExpression *node) {

  switch (node->getKind()) {
  case BinderKindUtils::BoundNodeKind::LiteralExpression: {
    BoundLiteralExpression<int> *literalExpression =
        (BoundLiteralExpression<int> *)node;

    return (int)(literalExpression->getValue());
  }
  case BinderKindUtils::BoundNodeKind::UnaryExpression: {
    BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)node;
    int operand = Evaluator::evaluate(unaryExpression->getOperand());
    switch (unaryExpression->getOperator()) {
    case BinderKindUtils::BoundUnaryOperatorKind::Identity:
      return operand;
    case BinderKindUtils::BoundUnaryOperatorKind::Negation:
      return -operand;
    default:
      throw "Unexpected unary operator";
    }
  }
  case BinderKindUtils::BoundNodeKind::BinaryExpression: {
    BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)node;
    int left = Evaluator::evaluate(binaryExpression->getLeft());
    int right = Evaluator::evaluate(binaryExpression->getRight());
    switch (binaryExpression->getOperator()) {
    case BinderKindUtils::BoundBinaryOperatorKind::Addition:
      return left + right;
    case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
      return left - right;
    case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
      return left * right;
    case BinderKindUtils::BoundBinaryOperatorKind::Division: {
      if (right == 0) {
        throw "ERROR: Division by zero";
      }
      return left / right;
    }
    default:
      throw "Unexpected binary operator";
    }
  }
  case BinderKindUtils::BoundNodeKind::ParenthesizedExpression: {
    BoundParenthesizedExpression *parenthesizedExpression =
        (BoundParenthesizedExpression *)node;
    return Evaluator::evaluate(parenthesizedExpression->getExpression());
  }
  default:
    throw "Unexpected node";
  }
}