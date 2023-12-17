#include "FillExpressionSyntax.h"

/*
    OVERRIDES

*/

SyntaxKindUtils::SyntaxKind FillExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FillExpression;
}

std::vector<SyntaxNode *> FillExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  _children.push_back(_sizeToFillExpression.get());
  _children.push_back(_elementExpression.get());

  return _children;
}

DiagnosticUtils::SourceLocation
FillExpressionSyntax::getSourceLocation() const {
  if (this->_sizeToFillExpression)
    return this->_sizeToFillExpression->getSourceLocation();

  if (this->_elementExpression)
    return this->_elementExpression->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}

/*
    SETTERS
*/

void FillExpressionSyntax::setSizeToFillExpression(
    std::unique_ptr<ExpressionSyntax> sizeToFillExpression) {
  this->_sizeToFillExpression = std::move(sizeToFillExpression);
}

void FillExpressionSyntax::setElementExpression(
    std::unique_ptr<ExpressionSyntax> elementExpression) {
  this->_elementExpression = std::move(elementExpression);
}

/*
    GETTERS
*/

auto FillExpressionSyntax::getSizeToFillExpressionRef() const
    -> const std::unique_ptr<ExpressionSyntax> & {
  return this->_sizeToFillExpression;
}

auto FillExpressionSyntax::getElementExpressionRef() const
    -> const std::unique_ptr<ExpressionSyntax> & {
  return this->_elementExpression;
}
