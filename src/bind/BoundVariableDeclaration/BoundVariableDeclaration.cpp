#include "BoundVariableDeclaration.h"

BoundVariableDeclaration::BoundVariableDeclaration(

    const std::string &lineAndColumn, std::string variable, bool isConst,
    std::shared_ptr<BoundExpression> initializer)
    : _variable(variable), _initializer(initializer), _isConst(isConst) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundVariableDeclaration::getKind() {
  return BinderKindUtils::BoundNodeKind::VariableDeclaration;
}

std::string BoundVariableDeclaration::getVariable() const { return _variable; }

std::shared_ptr<BoundExpression>
BoundVariableDeclaration::getInitializer() const {
  return _initializer;
}

bool BoundVariableDeclaration::isConst() const { return _isConst; }

std::vector<std::shared_ptr<BoundNode>>
BoundVariableDeclaration::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{_initializer};
}

std::string BoundVariableDeclaration::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
