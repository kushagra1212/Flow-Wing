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
  std::unique_ptr<BoundLiteralExpression<std::any>> _callerIdentifier;
  std::vector<std::unique_ptr<BoundExpression>> _arguments;

public:
  BoundCallExpression(
      std::string lineAndColumn,
      std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier,
      Utils::FunctionSymbol functionalSymbol);

  const std::string &getName() const;

  void addArgument(std::unique_ptr<BoundExpression> argument);

  std::vector<std::unique_ptr<BoundExpression>> &getArguments();

  const std::type_info &getType() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  std::unique_ptr<BoundLiteralExpression<std::any>> getCallerIdentifier();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};

#endif // __BOUND_CALL_EXPRESSION_H__