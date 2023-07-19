
#pragma once
#include "../../statements/StatementSyntax.h"
#include "../../syntax/CompilationUnitSyntax.h"
#include "../../syntax/SyntaxKindUtils.h"
#include "../../syntax/expression/AssignmentExpressionSyntax.h"
#include "../../syntax/expression/BinaryExpressionSyntax.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../syntax/expression/LiteralExpressionSyntax.h"
#include "../../syntax/expression/ParenthesizedExpressionSyntax.h"
#include "../../syntax/expression/UnaryExpressionSyntax.h"
#include "../../syntax/expression/VariableExpressionSyntax.h"
#include "../BinderKindUtils.h"
#include "../BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../BoundBinaryExpression/BoundBinaryExpression.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundUnaryExpression/BoundUnaryExpression.h"
#include "../BoundVariableExpression/BoundVariableExpression.h"
#include "BoundScope/BoundScope.h"
#include "BoundScopeGlobal/BoundScopeGlobal.h"
#include <stack>
class Binder {
private:
  std::vector<std::string> logs;

private:
  BoundScope *root;

public:
  Binder(BoundScope *root);

public:
  BoundExpression *bindExpression(ExpressionSyntax *syntax);

public:
  static BoundScopeGlobal *bindGlobalScope(BoundScopeGlobal *previous,
                                           CompilationUnitSyntax *syntax);

public:
  static BoundScope *CreateParentScope(BoundScopeGlobal *parent);

public:
  BoundStatement *Binder::bindStatement(StatementSyntax *syntax);
};
