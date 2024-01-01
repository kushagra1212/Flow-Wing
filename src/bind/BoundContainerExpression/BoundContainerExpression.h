#ifndef __BOUND_CONTAINER_EXPRESSION_H__
#define __BOUND_CONTAINER_EXPRESSION_H__

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundContainerExpression : public BoundExpression {
private:
  std::vector<std::unique_ptr<BoundExpression>> _elements;

public:
  BoundContainerExpression(const DiagnosticUtils::SourceLocation &location);

  // OVERRIDES
  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  // SETTERS
  void setElement(std::unique_ptr<BoundExpression> element);

  // GETTERS
  auto getElementsRef() const
      -> const std::vector<std::unique_ptr<BoundExpression>> &;
};

#endif // __BOUND_CONTAINER_EXPRESSION_H__