#ifndef __BOUND_CALL_EXPRESSION_H__
#define __BOUND_CALL_EXPRESSION_H__

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundNode.h"

class BoundCallExpression : public BoundExpression {
public:
  BoundCallExpression(const std::string &lineAndColumn,
                      BoundLiteralExpression<std::any> *callerIdentifier,
                      Utils::FunctionSymbol functionalSymbol,
                      const std::vector<BoundExpression *> &arguments);

  ~BoundCallExpression();

  const std::string &getName() const;
  const std::vector<BoundExpression *> &getArguments() const;

  BinderKindUtils::BoundNodeKind getKind() override;

  const std::type_info &getType() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  BoundLiteralExpression<std::any> *getCallerIdentifier() const;

  std::vector<BoundNode *> getChildren() override;

  std::string getLineNumberAndColumn() const override;

private:
  Utils::FunctionSymbol functionalSymbol;
  BoundLiteralExpression<std::any> *_callerIdentifier;
  std::vector<BoundExpression *> arguments;
};

#endif // __BOUND_CALL_EXPRESSION_H__