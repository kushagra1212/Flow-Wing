#include "TypeExpressionSyntax.h"

TypeExpressionSyntax::TypeExpressionSyntax(Utils::type type) : _type(type) {}

SyntaxKindUtils::SyntaxKind TypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::PrimitiveTypeExpression;
}

std::vector<SyntaxNode *> TypeExpressionSyntax::getChildren() { return {}; }

DiagnosticUtils::SourceLocation
TypeExpressionSyntax::getSourceLocation() const {
  return {};
}