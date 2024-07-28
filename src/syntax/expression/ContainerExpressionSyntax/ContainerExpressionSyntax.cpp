#include "ContainerExpressionSyntax.h"

/*
  OVERRIDES
*/

const SyntaxKindUtils::SyntaxKind ContainerExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContainerExpression;
}

const std::vector<SyntaxNode *> &ContainerExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (_openBracket)
    _children.push_back(_openBracket.get());

  for (auto &element : this->_elements)
    _children.push_back(element.get());

  if (_closeBracket)
    _children.push_back(_closeBracket.get());
  return _children;
}

const DiagnosticUtils::SourceLocation
ContainerExpressionSyntax::getSourceLocation() const {
  if (this->_elements.size() == 0) {
    if (_openBracket)
      return _openBracket->getSourceLocation();

    if (_closeBracket)
      return _closeBracket->getSourceLocation();
  }

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
