#include "ArrayTypeExpressionSyntax.h"

ArrayTypeExpressionSyntax::ArrayTypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : TypeExpressionSyntax(std::move(type)) {}

const std::vector<SyntaxNode *> &ArrayTypeExpressionSyntax::getChildren() {
  if (this->_children.empty()) {
    if (_nonTrivialElementType)
      _children.push_back(this->_nonTrivialElementType.get());
    if (_elementType)
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
  if (_elementType)
    return this->_elementType->getSourceLocation();
  if (_nonTrivialElementType)
    return this->_nonTrivialElementType->getSourceLocation();

  for (auto &dimension : this->_dimensions) {
    if (dimension)
      return dimension->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}