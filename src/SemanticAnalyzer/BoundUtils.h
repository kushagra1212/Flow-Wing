#pragma once

#include "BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"

class BoundUtils {
public:
  ~BoundUtils() = default;
  static BoundCallExpression *getCallExpression(BoundExpression *expression) {

    if (expression->getKind() ==
        BinderKindUtils::BoundNodeKind::CallExpression) {

      return static_cast<BoundCallExpression *>(expression);

    } else if (expression->getKind() ==
               BinderKindUtils::BoundNodeKind::VariableExpression) {

      BoundVariableExpression *variableExpression =
          static_cast<BoundVariableExpression *>(expression);

      for (auto &expr : variableExpression->getDotExpressionList()) {
        if (expr->getKind() == BinderKindUtils::BoundNodeKind::CallExpression) {
          return static_cast<BoundCallExpression *>(expr.get());
        }
      }
    }

    return nullptr;
  }
};