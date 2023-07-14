
#include "Binder.h"

BoundExpression *Binder::bindExpression(ExpressionSyntax *syntax) {
  switch (syntax->getKind()) {
  case SyntaxKindUtils::SyntaxKind::LiteralExpression: {
    LiteralExpressionSyntax<int> *numberExpression =
        (LiteralExpressionSyntax<int> *)syntax;

    return new BoundLiteralExpression(numberExpression->getValue());
  }
  case SyntaxKindUtils::SyntaxKind::UnaryExpression: {
    UnaryExpressionSyntax *unaryExpression = (UnaryExpressionSyntax *)syntax;
    BoundExpression *operand = bindExpression(unaryExpression->getOperand());
    BinderKindUtils::BoundUnaryOperatorKind op;

    if (operand->getType() != typeid(int)) {
      logs.push_back("Unary operator can only be applied to numbers");
      return operand;
    }

    switch (unaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::Identity;
      break;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      op = BinderKindUtils::BoundUnaryOperatorKind::Negation;
      break;
    default:
      throw "Unexpected unary operator";
    }
    return new BoundUnaryExpression(op, operand);
  }
  case SyntaxKindUtils::SyntaxKind::BinaryExpression: {
    BinaryExpressionSyntax *binaryExpression = (BinaryExpressionSyntax *)syntax;
    BoundExpression *left = bindExpression(binaryExpression->getLeft());
    BoundExpression *right = bindExpression(binaryExpression->getRight());
    BinderKindUtils::BoundBinaryOperatorKind op;

    if (left->getType() != typeid(int) || right->getType() != typeid(int)) {
      logs.push_back("Binary operator can only be applied to numbers");
      return left;
    }

    switch (binaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Addition;
      break;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Subtraction;
      break;
    case SyntaxKindUtils::SyntaxKind::StarToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Multiplication;
      break;
    case SyntaxKindUtils::SyntaxKind::SlashToken:
      op = BinderKindUtils::BoundBinaryOperatorKind::Division;
      break;
    default:
      throw "Unexpected binary operator";
    }
    return new BoundBinaryExpression(left, op, right);
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    ParenthesizedExpressionSyntax *parenthesizedExpression =
        (ParenthesizedExpressionSyntax *)syntax;
    return bindExpression(parenthesizedExpression->getExpression());
  }
  default:
    throw "Unexpected syntax";
  }
}
