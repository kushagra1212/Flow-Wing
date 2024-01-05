#include "ArrayTypeExpressionSyntax.h"

ArrayTypeExpressionSyntax::ArrayTypeExpressionSyntax(Utils::type type)
    : TypeExpressionSyntax(type) {}

std::vector<SyntaxNode *> ArrayTypeExpressionSyntax::getChildren() {
  if (this->_children.empty()) {
    for (auto &dimension : this->_dimensions) {
      this->_children.push_back(dimension.get());
    }
  }

  return this->_children;
}

SyntaxKindUtils::SyntaxKind ArrayTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::ArrayTypeExpression;
}