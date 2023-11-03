#include "BoundVariableDeclaration.h"

BoundVariableDeclaration::BoundVariableDeclaration(

    const DiagnosticUtils::SourceLocation &location, std::string variable,
    bool isConst, std::unique_ptr<BoundExpression> initializer)
    : BoundSourceLocation(location) {
  this->_variable = variable;
  this->_isConst = isConst;
  this->_initializer = std::move(initializer);

  this->_children.push_back(this->_initializer.get());
}

std::string BoundVariableDeclaration::getVariable() const { return _variable; }

std::unique_ptr<BoundExpression> BoundVariableDeclaration::getInitializer() {
  return std::move(_initializer);
}
BinderKindUtils::BoundNodeKind BoundVariableDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::VariableDeclaration;
}

bool BoundVariableDeclaration::isConst() const { return _isConst; }

std::vector<BoundNode *> BoundVariableDeclaration::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &
BoundVariableDeclaration::getInitializerPtr() {
  return this->_initializer;
}
