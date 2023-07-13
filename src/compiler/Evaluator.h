
#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "../syntax/SyntaxKindUtils.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/ExpressionSyntax.h"
#include "../syntax/expression/NumberExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"

class Evaluator {
public:
  static int evaluate(ExpressionSyntax *node);
};
#endif