#ifndef __BOUND_CALL_EXPRESSION_H__
#define __BOUND_CALL_EXPRESSION_H__

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundNode.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundCallExpression : public BoundExpression {
 private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _callerIdentifier;
  std::vector<std::unique_ptr<BoundExpression>> _arguments;
  std::string _callerName = "";

 public:
  BoundCallExpression(const DiagnosticUtils::SourceLocation &location);

  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  void addArgument(std::unique_ptr<BoundExpression> argument);
  void setCallerIdentifier(
      std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier);

  const std::vector<std::unique_ptr<BoundExpression>> &getArgumentsRef() const;
  std::unique_ptr<BoundLiteralExpression<std::any>> &getCallerIdentifierPtr();
  inline auto getCallerNameRef() const -> const std::string & {
    return _callerName;
  }
};

#endif  // __BOUND_CALL_EXPRESSION_H__