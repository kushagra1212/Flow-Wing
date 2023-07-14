#include "LiteralExpressionSyntax.h"
template <typename T>
LiteralExpressionSyntax<T>::LiteralExpressionSyntax(SyntaxToken *token,
                                                    T value) {

  this->token = token;
  this->value = value;

  children.push_back(this->token);
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
  return children;
}
template <typename T> T LiteralExpressionSyntax<T>::getValue() {
  return this->value;
}
template class LiteralExpressionSyntax<int>;
template class LiteralExpressionSyntax<bool>;