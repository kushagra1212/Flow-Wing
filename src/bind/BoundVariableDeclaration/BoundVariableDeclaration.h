#pragma once
#include "../../Common.h"
#include "../../syntax/expression/ExpressionSyntax.h"
#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundVariableDeclaration : public BoundStatement,
                                 public BoundSourceLocation {
private:
  std::string _variable;
  std::unique_ptr<BoundExpression> _initializer;
  bool _isConst;
  Utils::type _type;

public:
  BoundVariableDeclaration(const DiagnosticUtils::SourceLocation &location,
                           std::string variable, bool isConst, Utils::type type,
                           std::unique_ptr<BoundExpression> initializer);

  std::string getVariable() const;

  std::unique_ptr<BoundExpression> getInitializer();

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const;

  bool isConst() const;

  std::unique_ptr<BoundExpression> &getInitializerPtr();

  Utils::type getType() const;
};
