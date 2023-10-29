#ifndef __BOUND_CALL_EXPRESSION_H__
#define __BOUND_CALL_EXPRESSION_H__

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundNode.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundCallExpression : public BoundExpression, public BoundSourceLocation {
private:
  Utils::FunctionSymbol _functionalSymbol;
  std::unique_ptr<BoundLiteralExpression<std::any>> _callerIdentifier;
  std::vector<std::unique_ptr<BoundExpression>> _arguments;

public:
  BoundCallExpression(
      const DiagnosticUtils::SourceLocation &location,
      std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier,
      Utils::FunctionSymbol functionalSymbol);

  const std::string &getName() const;

  void addArgument(std::unique_ptr<BoundExpression> argument);

  std::vector<std::unique_ptr<BoundExpression>> &getArguments();

  std::unique_ptr<BoundLiteralExpression<std::any>> getCallerIdentifier();

  const std::type_info &getType() override;

  Utils::FunctionSymbol getFunctionSymbol() const;

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundLiteralExpression<std::any>> &getCallerIdentifierPtr();
};

#endif // __BOUND_CALL_EXPRESSION_H__