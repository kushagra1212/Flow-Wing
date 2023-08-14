#pragma once
#include "../../Common.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundVariableDeclaration : public BoundStatement {
private:
  std::string _variable;
  std::shared_ptr<BoundExpression> _initializer;
  bool _isConst;

public:
  BoundVariableDeclaration(

      const std::string &lineAndColumn, std::string variable, bool isConst,
      std::shared_ptr<BoundExpression> initializer);

  BinderKindUtils::BoundNodeKind getKind() override;
  std::string getVariable() const;
  std::shared_ptr<BoundExpression> getInitializer() const;

public:
  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

public:
  std::string getLineNumberAndColumn() const override;

  bool isConst() const;
};
