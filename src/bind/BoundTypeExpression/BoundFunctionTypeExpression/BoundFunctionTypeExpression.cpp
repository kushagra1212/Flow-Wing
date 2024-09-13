#include "BoundFunctionTypeExpression.h"

BoundFunctionTypeExpression::BoundFunctionTypeExpression(
    const DiagnosticUtils::SourceLocation &location,
    const SyntaxKindUtils::SyntaxKind &type)
    : BoundTypeExpression(location, type) {}

std::vector<BoundNode *> BoundFunctionTypeExpression::getChildren() {
  if (this->_children.empty()) {
    for (auto &parameterType : this->_parameterTypes) {
      this->_children.push_back(parameterType.get());
    }

    for (auto &returnType : this->_returnTypes) {
      this->_children.push_back(returnType.get());
    }
  }

  return this->_children;
}

BinderKindUtils::BoundNodeKind BoundFunctionTypeExpression::getKind() const {
  return BinderKindUtils::BoundFunctionTypeExpression;
}