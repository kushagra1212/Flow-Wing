#ifndef __BIND_INDEX_EXPRESSION_H__
#define __BIND_INDEX_EXPRESSION_H__

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundVariableExpression/BoundVariableExpression.h"
class BoundIndexExpression : public BoundExpression,
                             public BoundSourceLocation {
private:
  std::unique_ptr<BoundVariableExpression> _boundIdentifierExpression;
  std::unique_ptr<BoundLiteralExpression<std::any>> _boundIndexExpression;

public:
  BoundIndexExpression(
      const DiagnosticUtils::SourceLocation &location,
      std::unique_ptr<BoundVariableExpression> boundIdentifierExpression,
      std::unique_ptr<BoundLiteralExpression<std::any>> boundIndexExpression);

  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundVariableExpression> &getBoundIdentifierExpression();
  std::unique_ptr<BoundLiteralExpression<std::any>> &getBoundIndexExpression();
};

#endif // __BIND_INDEX_EXPRESSION_H__