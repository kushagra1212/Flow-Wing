#include "BoundVariableExpression.h"

BoundVariableExpression::BoundVariableExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
    const bool &isConstant,
    std::unique_ptr<BoundTypeExpression> variableTypeExp)
    : BoundExpression(location),
      _identiferExpression(std::move(identiferExpression)),
      _isConstant(isConstant), _variableTypeExp(std::move(variableTypeExp)) {}

const std::type_info &BoundVariableExpression::getType() {
  return this->_identiferExpression->getType();
}

BinderKindUtils::BoundNodeKind BoundVariableExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::VariableExpression;
}

std::vector<BoundNode *> BoundVariableExpression::getChildren() {
  if (_children.empty())
    this->_children.push_back(this->_identiferExpression.get());
  return this->_children;
}
