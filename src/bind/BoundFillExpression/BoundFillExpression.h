#ifndef __FLOWWING_BOUND_FILL_EXPRESSION_H__
#define __FLOWWING_BOUND_FILL_EXPRESSION_H__

#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundFillExpression : public BoundExpression {
 private:
  std::unique_ptr<BoundExpression> _elementToFill;
  std::unique_ptr<BoundExpression> _sizeToFill;

 public:
  BoundFillExpression(const DiagnosticUtils::SourceLocation &location);

  // OVERRIDES
  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  // SETTERS
  void setElementToFill(std::unique_ptr<BoundExpression> elementToFill);
  void setSizeToFill(std::unique_ptr<BoundExpression> sizeToFill);

  // GETTERS
  auto getElementToFillRef() const -> const std::unique_ptr<BoundExpression> &;
  auto getSizeToFillRef() const -> const std::unique_ptr<BoundExpression> &;
};

#endif  // __FLOWWING_BOUND_FILL_EXPRESSION_H__