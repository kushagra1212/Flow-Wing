#include "VariableDeclarationSyntax.h"

VariableDeclarationSyntax::VariableDeclarationSyntax(
    std::shared_ptr<SyntaxToken<std::any>> keyword,
    std::shared_ptr<SyntaxToken<std::any>> identifier,
    std::shared_ptr<SyntaxToken<std::any>> equalsToken,
    std::shared_ptr<ExpressionSyntax> initializer)
    : _keyword(keyword), _identifier(identifier), _equalsToken(equalsToken),
      _initializer(initializer) {}

SyntaxKindUtils::SyntaxKind VariableDeclarationSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::VariableDeclaration;
}

std::vector<std::shared_ptr<SyntaxNode>>
VariableDeclarationSyntax::getChildren() {
  return std::vector<std::shared_ptr<SyntaxNode>>{_keyword, _identifier,
                                                  _equalsToken, _initializer};
}

std::shared_ptr<SyntaxToken<std::any>>
VariableDeclarationSyntax::getIdentifier() const {
  return _identifier;
}

std::shared_ptr<SyntaxToken<std::any>>
VariableDeclarationSyntax::getEqualsToken() const {
  return _equalsToken;
}

std::shared_ptr<ExpressionSyntax>
VariableDeclarationSyntax::getInitializer() const {
  return _initializer;
}

std::shared_ptr<SyntaxToken<std::any>>
VariableDeclarationSyntax::getKeyword() const {
  return _keyword;
}

std::string VariableDeclarationSyntax::getLineNumberAndColumn() const {
  return _keyword->getLineNumberAndColumn();
}

// Path:
// src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h