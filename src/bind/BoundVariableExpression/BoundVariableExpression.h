#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundTypeExpression/BoundTypeExpression.h"

class BoundVariableExpression : public BoundExpression {
 public:
  BoundVariableExpression(
      const DiagnosticUtils::SourceLocation &location,
      std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
      const bool &isConstant,
      std::unique_ptr<BoundTypeExpression> variableTypeExp);

  virtual const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  const std::unique_ptr<BoundLiteralExpression<std::any>> &
  getIdentifierExpressionPtr() const {
    return this->_identiferExpression;
  }

  inline auto getVariableNameRef() const -> const std::string {
    return std::any_cast<std::string>(_identiferExpression->getValue());
  }

  inline auto getVariableTypeRef() const
      -> const std::unique_ptr<BoundTypeExpression> & {
    return _variableTypeExp;
  }

  inline auto isConstant() const -> const bool { return _isConstant; }

  inline auto getDotExpressionList() const -> const
      std::vector<std::unique_ptr<BoundLiteralExpression<std::any>>> & {
    return _dotExpressionList;
  }

  inline void addDotExpression(
      std::unique_ptr<BoundLiteralExpression<std::any>> dotExpression) {
    _dotExpressionList.push_back(std::move(dotExpression));
  }

 private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _identiferExpression;
  std::vector<std::unique_ptr<BoundLiteralExpression<std::any>>>
      _dotExpressionList;
  bool _isConstant;
  std::unique_ptr<BoundTypeExpression> _variableTypeExp;
};