#include "ArrayTypeExpressionSyntax.h"

ArrayTypeExpressionSyntax::ArrayTypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : TypeExpressionSyntax(std::move(type)) {}

const std::vector<SyntaxNode *> &ArrayTypeExpressionSyntax::getChildren() {
  if (this->_children.empty()) {
    _children.push_back(this->getTypeRef().get());
    _children.push_back(this->_elementType.get());
    for (auto &dimension : this->_dimensions) {
      this->_children.push_back(dimension.get());
    }
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind ArrayTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::ArrayTypeExpression;
}
const DiagnosticUtils::SourceLocation
ArrayTypeExpressionSyntax::getSourceLocation() const {
  return this->_elementType->getSourceLocation();
}