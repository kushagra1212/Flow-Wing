#include "VariableDeclarationSyntax.h"

VariableDeclarationSyntax::VariableDeclarationSyntax(
    SyntaxToken<std::any> *keyword, SyntaxToken<std::any> *identifier,
    SyntaxToken<std::any> *equalsToken, ExpressionSyntax *initializer)
    : _keyword(keyword), _identifier(identifier), _equalsToken(equalsToken),
      _initializer(initializer) {}

SyntaxKindUtils::SyntaxKind VariableDeclarationSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::VariableDeclaration;
}

std::vector<SyntaxNode *> VariableDeclarationSyntax::getChildren() {
  return std::vector<SyntaxNode *>{_keyword, _identifier, _equalsToken,
                                   _initializer};
}

SyntaxToken<std::any> *VariableDeclarationSyntax::getIdentifier() const {
  return _identifier;
}

SyntaxToken<std::any> *VariableDeclarationSyntax::getEqualsToken() const {
  return _equalsToken;
}

ExpressionSyntax *VariableDeclarationSyntax::getInitializer() const {
  return _initializer;
}

SyntaxToken<std::any> *VariableDeclarationSyntax::getKeyword() const {
  return _keyword;
}
VariableDeclarationSyntax::~VariableDeclarationSyntax() {
  if (_keyword != nullptr) {
    delete _keyword;
    _keyword = nullptr;
  }

  if (_identifier != nullptr) {
    delete _identifier;
    _identifier = nullptr;
  }

  if (_equalsToken != nullptr) {
    delete _equalsToken;
    _equalsToken = nullptr;
  }

  if (_initializer != nullptr) {
    delete _initializer;
    _initializer = nullptr;
  }
}

// Path:
// src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h