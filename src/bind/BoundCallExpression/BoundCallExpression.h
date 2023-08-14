#ifndef __BOUND_CALL_EXPRESSION_H__
#define __BOUND_CALL_EXPRESSION_H__

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundNode.h"

class BoundCallExpression : public BoundExpression {
private:
  Utils::FunctionSymbol _functionalSymbol;
  std::shared_ptr<BoundLiteralExpression<std::any>> _callerIdentifier;
  std::vector<std::shared_ptr<BoundExpression>> _arguments;

public:
  BoundCallExpression(
      const std::string &lineAndColumn,
      std::shared_ptr<BoundLiteralExpression<std::any>> callerIdentifier,
      Utils::FunctionSymbol functionalSymbol,
      const std::vector<std::shared_ptr<BoundExpression>> &arguments);

  const std::string &getName() const;
  const std::vector<std::shared_ptr<BoundExpression>> &getArguments() const;

  BinderKindUtils::BoundNodeKind getKind() override;

  const std::type_info &getType() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  std::shared_ptr<BoundLiteralExpression<std::any>> getCallerIdentifier() const;

  std::vector<std::shared_ptr<BoundNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // __BOUND_CALL_EXPRESSION_H__