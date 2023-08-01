#include "BoundVariableDeclaration.h"

BoundVariableDeclaration::BoundVariableDeclaration(std::string variable,
                                                   bool isConst,
                                                   BoundExpression *initializer)
    : _variable(variable), _initializer(initializer), _isConst(isConst) {}

BinderKindUtils::BoundNodeKind BoundVariableDeclaration::getKind() {
  return BinderKindUtils::BoundNodeKind::VariableDeclaration;
}

std::string BoundVariableDeclaration::getVariable() const { return _variable; }

BoundExpression *BoundVariableDeclaration::getInitializer() const {
  return _initializer;
}

bool BoundVariableDeclaration::isConst() const { return _isConst; }

BoundVariableDeclaration::~BoundVariableDeclaration() { delete _initializer; }
