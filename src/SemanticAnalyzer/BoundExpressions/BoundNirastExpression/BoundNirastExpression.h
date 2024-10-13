#ifndef __BOUND_NIRAST_EXPRESSION_H__
#define __BOUND_NIRAST_EXPRESSION_H__

#include "../BoundExpression/BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"

class BoundNirastExpression : public BoundExpression {
  std::unique_ptr<BoundLiteralExpression<std::any>> _nirastExpression;

public:
  BoundNirastExpression(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline virtual const std::type_info &getType() override {
    return typeid(BoundNirastExpression);
  }

  /*
    Setters
  */

  inline auto setNirastExpression(
      std::unique_ptr<BoundLiteralExpression<std::any>> nirastExpression)
      -> void {
    this->_nirastExpression = std::move(nirastExpression);
  }

  /*
    Getters
  */

  inline auto getNirastExpressionRef() const
      -> const std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return this->_nirastExpression;
  }
};

#endif