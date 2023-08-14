#include "LiteralExpressionSyntax.h"

template class LiteralExpressionSyntax<std::any>;
template class LiteralExpressionSyntax<int>;
template class LiteralExpressionSyntax<double>;
template class LiteralExpressionSyntax<bool>;
template class LiteralExpressionSyntax<std::string>;
template class LiteralExpressionSyntax<char>;
template <typename T>
LiteralExpressionSyntax<T>::LiteralExpressionSyntax(
    std::shared_ptr<SyntaxToken<std::any>> token, T value) {

  this->_token = token;
  this->_value = value;
}
template <typename T>
SyntaxKindUtils::SyntaxKind LiteralExpressionSyntax<T>::getKind() {
  return SyntaxKindUtils::SyntaxKind::LiteralExpression;
}
template <typename T> std::string LiteralExpressionSyntax<T>::getKindText() {
  return SyntaxKindUtils::to_string(this->getKind());
}
template <typename T>
std::shared_ptr<SyntaxToken<std::any>> LiteralExpressionSyntax<T>::getToken() {
  return this->_token;
}
template <typename T>
std::vector<std::shared_ptr<SyntaxNode>>
LiteralExpressionSyntax<T>::getChildren() {

  std::vector<std::shared_ptr<SyntaxNode>> children = {this->_token};
  return children;
}
template <typename T> T LiteralExpressionSyntax<T>::getValue() {
  return this->_value;
}

template <typename T>
std::string LiteralExpressionSyntax<T>::getLineNumberAndColumn() const {
  return this->_token->getLineNumberAndColumn();
}
