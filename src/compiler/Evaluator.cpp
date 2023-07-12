
#include "../syntax/SyntaxKindUtils.cpp"
#include "../syntax/expression/BinaryExpressionSyntax.cpp"
#include "../syntax/expression/ExpressionSyntax.h"
#include "../syntax/expression/NumberExpressionSyntax.cpp"
#include "../syntax/expression/ParenthesizedExpressionSyntax.cpp"

class Evaluator {
public:
  static int evaluate(ExpressionSyntax *node) {

    switch (node->getKind()) {
    case SyntaxKindUtils::NumberExpression: {
      NumberExpressionSyntax *numberExpression = (NumberExpressionSyntax *)node;

      return (int)(numberExpression->getNumberToken()->getValue());
    }
    case SyntaxKindUtils::BinaryExpression: {
      BinaryExpressionSyntax *binaryExpression = (BinaryExpressionSyntax *)node;
      int left = Evaluator::evaluate(binaryExpression->getLeft());
      int right = Evaluator::evaluate(binaryExpression->getRight());
      switch (binaryExpression->getOperatorToken()->getKind()) {
      case SyntaxKindUtils::PlusToken:
        return left + right;
      case SyntaxKindUtils::MinusToken:
        return left - right;
      case SyntaxKindUtils::StarToken:
        return left * right;
      case SyntaxKindUtils::SlashToken: {
        if (right == 0) {
          throw "ERROR: Division by zero";
        }
        return left / right;
      }
      default:
        throw "Unexpected binary operator";
      }
    }
    case SyntaxKindUtils::ParenthesizedExpression: {
      ParenthesizedExpressionSyntax *parenthesizedExpression =
          (ParenthesizedExpressionSyntax *)node;
      return Evaluator::evaluate(parenthesizedExpression->getExpression());
    }
    default:
      throw "Unexpected node";
    }
  }
};