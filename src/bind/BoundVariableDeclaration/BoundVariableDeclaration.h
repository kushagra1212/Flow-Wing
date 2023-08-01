#pragma once
#include "../../Common.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundVariableDeclaration : public BoundStatement {
private:
  std::string _variable;
  BoundExpression *_initializer;
  bool _isConst;

public:
  BoundVariableDeclaration(std::string variable, bool isConst,
                           BoundExpression *initializer);

  ~BoundVariableDeclaration();
  BinderKindUtils::BoundNodeKind getKind() override;
  std::string getVariable() const;
  BoundExpression *getInitializer() const;

  bool isConst() const;
};
