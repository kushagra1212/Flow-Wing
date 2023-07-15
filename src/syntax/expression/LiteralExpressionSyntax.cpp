#include "LiteralExpressionSyntax.h"

template class LiteralExpressionSyntax<int>;
template class LiteralExpressionSyntax<double>;
template class LiteralExpressionSyntax<bool>;
template class LiteralExpressionSyntax<std::string>;
template class LiteralExpressionSyntax<char>;

template <typename T>
LiteralExpressionSyntax<T>::LiteralExpressionSyntax(SyntaxToken *token,
                                                    T value) {

  this->token = token;
  this->value = value;
}
template <typename T>
SyntaxKindUtils::SyntaxKind LiteralExpressionSyntax<T>::getKind() {
  return SyntaxKindUtils::SyntaxKind::LiteralExpression;
}
template <typename T> std::string LiteralExpressionSyntax<T>::getKindText() {
  return SyntaxKindUtils::enum_to_string_map[this->getKind()];
}
template <typename T> SyntaxToken *LiteralExpressionSyntax<T>::getToken() {
  return this->token;
}
template <typename T>
std::vector<SyntaxNode *> LiteralExpressionSyntax<T>::getChildren() {

  std::vector<SyntaxNode *> children = {this->token};
  return children;
}
template <typename T> T LiteralExpressionSyntax<T>::getValue() {
  return this->value;
}
