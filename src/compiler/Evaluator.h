
#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "../bind/Binder/Binder.h"
#include "../syntax/SyntaxKindUtils.h"
#include "../syntax/expression/BinaryExpressionSyntax.h"
#include "../syntax/expression/ExpressionSyntax.h"
#include "../syntax/expression/LiteralExpressionSyntax.h"
#include "../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../syntax/expression/UnaryExpressionSyntax.h"

#include "../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../bind/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../bind/BoundExpression.h"
#include "../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include <any>
#include <string>
#include <unordered_map>
class Evaluator {

public:
  template <typename T> static T evaluate(BoundExpression *node);

  static std::unordered_map<std::string, std::any> variables;
  template <typename T>
  static T
  binaryExpressionEvaluator(BinderKindUtils::BoundBinaryOperatorKind op,
                            int left, int right);
};
#endif