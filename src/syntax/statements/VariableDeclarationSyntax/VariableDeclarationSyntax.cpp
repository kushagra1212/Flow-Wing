#include "VariableDeclarationSyntax.h"

VariableDeclarationSyntax::VariableDeclarationSyntax(
    std::unique_ptr<SyntaxToken<std::any>> keyword,
    std::unique_ptr<SyntaxToken<std::any>> identifier,
    std::unique_ptr<SyntaxToken<std::any>> equalsToken,
    std::unique_ptr<ExpressionSyntax> initializer, Utils::type type) {
  this->_keyword = std::move(keyword);
  this->_identifier = std::move(identifier);
  this->_equalsToken = std::move(equalsToken);
  this->_initializer = std::move(initializer);
  this->_type = type;
  // Add children

  _children.push_back(_keyword.get());
  _children.push_back(_identifier.get());
  _children.push_back(_equalsToken.get());

  if (_initializer != nullptr) {
    _children.push_back(_initializer.get());
  }
}

std::unique_ptr<SyntaxToken<std::any>>
VariableDeclarationSyntax::getIdentifier() {
  return std::move(_identifier);
}

std::unique_ptr<SyntaxToken<std::any>>
VariableDeclarationSyntax::getEqualsToken() {
  return std::move(_equalsToken);
}

std::unique_ptr<ExpressionSyntax> VariableDeclarationSyntax::getInitializer() {
  return std::move(_initializer);
}

std::unique_ptr<ExpressionSyntax> &
VariableDeclarationSyntax::getInitializerPtr() {
  return (_initializer);
}

std::unique_ptr<SyntaxToken<std::any>> VariableDeclarationSyntax::getKeyword() {
  return std::move(_keyword);
}
std::unique_ptr<SyntaxToken<std::any>> &
VariableDeclarationSyntax::getIdentifierPtr() {
  return (_identifier);
}

SyntaxKindUtils::SyntaxKind VariableDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableDeclaration;
}

std::vector<SyntaxNode *> VariableDeclarationSyntax::getChildren() {
  return this->_children;
}

DiagnosticUtils::SourceLocation
VariableDeclarationSyntax::getSourceLocation() const {
  return this->_keyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
VariableDeclarationSyntax::getEqualsTokenPtr() {
  return this->_equalsToken;
}
std::unique_ptr<SyntaxToken<std::any>> &
VariableDeclarationSyntax::getKeywordPtr() {
  return this->_keyword;
}

const Utils::type VariableDeclarationSyntax::getType() const {
  return this->_type;
}

// Path:
// src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h