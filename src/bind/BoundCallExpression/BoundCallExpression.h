#ifndef __BOUND_CALL_EXPRESSION_H__
#define __BOUND_CALL_EXPRESSION_H__

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundNode.h"

class BoundCallExpression : public BoundExpression {
public:
  BoundCallExpression(Utils::FunctionSymbol functionalSymbol,
                      const std::vector<BoundExpression *> &arguments);

  ~BoundCallExpression();

  const std::string &getName() const;
  const std::vector<BoundExpression *> &getArguments() const;

  BinderKindUtils::BoundNodeKind getKind() override;

  const std::type_info &getType() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  std::vector<BoundNode *> getChildren() override;

private:
  Utils::FunctionSymbol functionalSymbol;
  std::vector<BoundExpression *> arguments;
};

#endif // __BOUND_CALL_EXPRESSION_H__