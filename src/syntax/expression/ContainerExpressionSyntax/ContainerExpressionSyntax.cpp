#include "ContainerExpressionSyntax.h"

/*
  OVERRIDES
*/

const SyntaxKindUtils::SyntaxKind ContainerExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContainerExpression;
}

const std::vector<SyntaxNode *> &ContainerExpressionSyntax::getChildren() {
  if (_children.size() > 0) return _children;

  for (auto &element : this->_elements) _children.push_back(element.get());

  return _children;
}

const DiagnosticUtils::SourceLocation
ContainerExpressionSyntax::getSourceLocation() const {
  if (this->_elements.size() == 0) return DiagnosticUtils::SourceLocation();

  return this->_elements[0]->getSourceLocation();
}

/*
  SETTERS
*/

auto ContainerExpressionSyntax::setElement(
    std::unique_ptr<ExpressionSyntax> element) -> void {
  this->_elements.push_back(std::move(element));
}

/*
  GETTERS
*/

auto ContainerExpressionSyntax::getElementsRef() const
    -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
  return this->_elements;
}
