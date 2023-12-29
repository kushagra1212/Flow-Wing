#include "BoundArrayVariableExpression.h"

BoundArrayVariableExpression::BoundArrayVariableExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
    const bool &isConstant, const Utils::type &variableType)
    : BoundVariableExpression(location, std::move(identiferExpression),
                              isConstant, variableType) {}

const std::type_info &BoundArrayVariableExpression::getType() {
  return typeid(std::vector<std::any>);
}

BinderKindUtils::BoundNodeKind BoundArrayVariableExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::ArrayVariableExpression;
}

std::vector<BoundNode *> BoundArrayVariableExpression::getChildren() {

  if (this->_children.size() == 0) {
    this->_children.push_back(this->getIdentifierExpressionPtr().get());
    for (const auto &sizeExpression : this->_sizeExpressions) {
      this->_children.push_back(sizeExpression.get());
    }
  }

  return this->_children;
}

void BoundArrayVariableExpression::addSizeExpression(
    std::unique_ptr<BoundExpression> sizeExpression) {
  this->_sizeExpressions.push_back(std::move(sizeExpression));
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundArrayVariableExpression::getSizeExpressionsRef() const {
  return this->_sizeExpressions;
}