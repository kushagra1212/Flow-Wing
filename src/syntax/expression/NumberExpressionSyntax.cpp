#include "NumberExpressionSyntax.h"

NumberExpressionSyntax::NumberExpressionSyntax(SyntaxToken *numberToken) {

  this->numberToken = numberToken;

  children.push_back(this->numberToken);
}

SyntaxKindUtils::SyntaxKind NumberExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::LiteralExpression;
}
std::string NumberExpressionSyntax::getKindText() {
  return SyntaxKindUtils::enum_to_string_map[this->getKind()];
}

SyntaxToken *NumberExpressionSyntax::getNumberToken() {
  return this->numberToken;
}

std::vector<SyntaxNode *> NumberExpressionSyntax::getChildren() {
  return children;
}