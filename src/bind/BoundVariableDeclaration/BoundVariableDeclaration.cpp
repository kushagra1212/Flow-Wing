#include "BoundVariableDeclaration.h"

BoundVariableDeclaration::BoundVariableDeclaration(
    const DiagnosticUtils::SourceLocation &location,
    const std::string &variableName, bool isConst, bool isExposed)
    : BoundSourceLocation(location), _variableName(variableName),
      _isConst(isConst), _isExposed(isExposed) {}

std::unique_ptr<BoundExpression> BoundVariableDeclaration::getInitializer() {
  return std::move(_initializer);
}

BinderKindUtils::BoundNodeKind BoundVariableDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::VariableDeclaration;
}

BinderKindUtils::MemoryKind BoundVariableDeclaration::getMemoryKind() const {
  return _memoryKind;
};

bool BoundVariableDeclaration::isConst() const { return _isConst; }

std::vector<BoundNode *> BoundVariableDeclaration::getChildren() {
  if (_children.empty()) {
    if (_typeExp)
      _children.push_back(this->_typeExp.get());
    if (_identifier)
      _children.push_back(this->_identifier.get());
    if (_initializer)
      _children.push_back(this->_initializer.get());
  }

  return this->_children;
}

std::unique_ptr<BoundExpression> &
BoundVariableDeclaration::getInitializerPtr() {
  return this->_initializer;
}

const std::string &BoundVariableDeclaration::getVariableName() const {
  return _variableName;
}
