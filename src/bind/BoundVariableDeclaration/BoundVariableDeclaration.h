#pragma once
#include "../../Common.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundVariableDeclaration : public BoundStatement {
private:
  std::string _variable;
  std::unique_ptr<BoundExpression> _initializer;
  bool _isConst;

public:
  BoundVariableDeclaration(std::string lineAndColumn, std::string variable,
                           bool isConst,
                           std::unique_ptr<BoundExpression> initializer);

  std::string getVariable() const;

  std::unique_ptr<BoundExpression> getInitializer();

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::string getLineNumberAndColumn() override;

  bool isConst() const;

  std::unique_ptr<BoundExpression> &getInitializerPtr();
};
