#include "Evaluator.h"

int Evaluator::evaluate(ExpressionSyntax *node) {

  switch (node->getKind()) {
  case SyntaxKindUtils::SyntaxKind::NumberExpression: {
    NumberExpressionSyntax *numberExpression = (NumberExpressionSyntax *)node;

    return (int)(numberExpression->getNumberToken()->getValue());
  }
  case SyntaxKindUtils::BinaryExpression: {
    BinaryExpressionSyntax *binaryExpression = (BinaryExpressionSyntax *)node;
    int left = Evaluator::evaluate(binaryExpression->getLeft());
    int right = Evaluator::evaluate(binaryExpression->getRight());
    switch (binaryExpression->getOperatorToken()->getKind()) {
    case SyntaxKindUtils::SyntaxKind::PlusToken:
      return left + right;
    case SyntaxKindUtils::SyntaxKind::MinusToken:
      return left - right;
    case SyntaxKindUtils::SyntaxKind::StarToken:
      return left * right;
    case SyntaxKindUtils::SyntaxKind::SlashToken: {
      if (right == 0) {
        throw "ERROR: Division by zero";
      }
      return left / right;
    }
    default:
      throw "Unexpected binary operator";
    }
  }
  case SyntaxKindUtils::SyntaxKind::ParenthesizedExpression: {
    ParenthesizedExpressionSyntax *parenthesizedExpression =
        (ParenthesizedExpressionSyntax *)node;
    return Evaluator::evaluate(parenthesizedExpression->getExpression());
  }
  default:
    throw "Unexpected node";
  }
}