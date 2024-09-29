#include "FunctionTypeExpressionSyntax.h"

FunctionTypeExpressionSyntax::FunctionTypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : TypeExpressionSyntax(std::move(type)) {}

const SyntaxKindUtils::SyntaxKind
FunctionTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::FunctionTypeExpression;
}

const std::vector<SyntaxNode *> &FunctionTypeExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (this->_openBracketToken)
    _children.push_back(_openBracketToken.get());

  if (this->_openParenthesisToken)
    _children.push_back(_openParenthesisToken.get());

  for (auto &parameterType : _parameterTypes)
    _children.push_back(parameterType.get());

  for (auto &asType : _asParametersKeywords) {
    _children.push_back(asType.second.get());
  }

  if (this->_closeParenthesisToken)
    _children.push_back(_closeParenthesisToken.get());

  if (this->_asKeyword)
    _children.push_back(_asKeyword.get());

  for (auto &returnType : _returnTypes) {
    _children.push_back(returnType.get());
  }

  if (this->_closeBracketToken)
    _children.push_back(_closeBracketToken.get());

  return _children;
}

const DiagnosticUtils::SourceLocation
FunctionTypeExpressionSyntax::getSourceLocation() const {

  if (_openParenthesisToken)
    return _openParenthesisToken->getSourceLocation();

  for (auto &parameterType : _parameterTypes) {
    if (parameterType)
      return parameterType->getSourceLocation();
  }
  for (auto &asType : _asParametersKeywords) {
    return (asType.second->getSourceLocation());
  }

  if (_closeParenthesisToken)
    return _closeParenthesisToken->getSourceLocation();

  if (_asKeyword)
    return _asKeyword->getSourceLocation();

  for (auto &returnType : _returnTypes)
    return returnType->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}