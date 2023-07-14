
#pragma once
#include "../../syntax/SyntaxKindUtils.h"
#include "../../syntax/expression/BinaryExpressionSyntax.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../syntax/expression/LiteralExpressionSyntax.h"
#include "../../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../../syntax/expression/UnaryExpressionSyntax.h"
#include "../BinderKindUtils.h"
#include "../BoundBinaryExpression/BoundBinaryExpression.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundUnaryExpression/BoundUnaryExpression.h"
class Binder {
public:
  std::vector<std::string> logs;
  BoundExpression *bindExpression(ExpressionSyntax *syntax);
};
