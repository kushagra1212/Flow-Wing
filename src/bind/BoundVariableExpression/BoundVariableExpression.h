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
      const bool &isConstant, BoundTypeExpression *variableTypeExp);

  virtual const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  const std::unique_ptr<BoundLiteralExpression<std::any>> &

  getIdentifierExpressionPtr() const {
    return this->_identiferExpression;
  }

  inline auto setHasNewKeyword(bool hasNewKeyword) {
    _hasNewKeyword = hasNewKeyword;
  }

  inline auto setSelf(bool isSelf) { _isSelf = isSelf; }

  inline auto getVariableNameRef() const -> const std::string {
    return std::any_cast<std::string>(_identiferExpression->getValue());
  }

  inline auto getVariableTypeRef() -> BoundTypeExpression * {
    return _variableTypeExp;
  }

  inline auto isConstant() const -> const bool { return _isConstant; }

  inline auto getDotExpressionList() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _dotExpressionList;
  }

  inline auto removeDotExpressionFromFront()
      -> std::unique_ptr<BoundExpression> {
    auto dotExpression = std::move(_dotExpressionList.front());
    _dotExpressionList.erase(_dotExpressionList.begin());
    return std::move(dotExpression);
  }

  inline void addDotExpression(std::unique_ptr<BoundExpression> dotExpression) {
    _dotExpressionList.push_back(std::move(dotExpression));
  }

  inline auto getHasNewKeyword() -> bool { return _hasNewKeyword; }

  inline auto isSelf() -> bool { return _isSelf; }

private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _identiferExpression;
  std::vector<std::unique_ptr<BoundExpression>> _dotExpressionList;
  bool _isConstant;
  BoundTypeExpression *_variableTypeExp;
  bool _hasNewKeyword;
  bool _isSelf = false;
};