#include "ArrayVariableExpressionSyntax.h"

ArrayVariableExpressionSyntax::ArrayVariableExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> identifierExpression,
    const bool isConstant, const Utils::type &variableType)
    : VariableExpressionSyntax(std::move(identifierExpression), isConstant,
                               variableType) {}

SyntaxKindUtils::SyntaxKind ArrayVariableExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ArrayVariableExpressionSyntax;
}

std::vector<SyntaxNode *> ArrayVariableExpressionSyntax::getChildren() {

  if (_children.empty()) {
    _children.push_back(getIdentifierTokenRef().get());
    for (const auto &sizeExpression : _sizeExpressions) {
      _children.push_back(sizeExpression.get());
    }
  }
  return _children;
}

DiagnosticUtils::SourceLocation
ArrayVariableExpressionSyntax::getSourceLocation() const {
  return DiagnosticUtils::SourceLocation();
}

void ArrayVariableExpressionSyntax::addSizeExpression(
    std::unique_ptr<ExpressionSyntax> sizeExpression) {
  _sizeExpressions.push_back(std::move(sizeExpression));
}
