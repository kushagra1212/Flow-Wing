#pragma once
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"

class BoundVariableExpression : public BoundExpression {

public:
  BoundVariableExpression(
      const DiagnosticUtils::SourceLocation &location,
      std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
      const bool &isConstant, const Utils::type &variableType);

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

  inline auto getVariableTypeRef() const -> const Utils::type & {
    return _variableType;
  }

  inline auto isConstant() const -> const bool { return _isConstant; }

private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _identiferExpression;
  bool _isConstant;
  Utils::type _variableType;
};