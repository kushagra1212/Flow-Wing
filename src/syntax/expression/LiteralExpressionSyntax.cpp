#include "LiteralExpressionSyntax.h"

template class LiteralExpressionSyntax<std::any>;
template class LiteralExpressionSyntax<int>;
template class LiteralExpressionSyntax<double>;
template class LiteralExpressionSyntax<bool>;
template class LiteralExpressionSyntax<std::string>;
template class LiteralExpressionSyntax<char>;
template <typename T>
LiteralExpressionSyntax<T>::LiteralExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> token, T value) {
  this->_token = std::move(token);
  this->_value = value;

  // Add children

  this->_children.push_back(_token.get());
}

template <typename T> std::string LiteralExpressionSyntax<T>::getKindText() {
  return SyntaxKindUtils::to_string(this->getKind());
}
template <typename T>
std::unique_ptr<SyntaxToken<std::any>> LiteralExpressionSyntax<T>::getToken() {
  return std::move(this->_token);
}

template <typename T> T LiteralExpressionSyntax<T>::getValue() {
  return this->_value;
}

template <typename T>
SyntaxKindUtils::SyntaxKind LiteralExpressionSyntax<T>::getKind() const {
  return SyntaxKindUtils::SyntaxKind::LiteralExpression;
}
template <typename T>
std::vector<SyntaxNode *> LiteralExpressionSyntax<T>::getChildren() {
  return this->_children;
}

template <typename T>
DiagnosticUtils::SourceLocation
LiteralExpressionSyntax<T>::getSourceLocation() const {
  return this->_token->getSourceLocation();
}

template <typename T>
std::unique_ptr<SyntaxToken<std::any>> &
LiteralExpressionSyntax<T>::getTokenPtr() {
  return this->_token;
}
