#include "BoundFunctionDeclaration.h"

BoundFunctionDeclaration::BoundFunctionDeclaration(
    std::string lineAndColumn,

    Utils::FunctionSymbol functionSymbol,
    std::unique_ptr<BoundBlockStatement> body) {
  this->_lineAndColumn = lineAndColumn;
  this->_functionSymbol = functionSymbol;
  this->_body = std::move(body);

  this->_children.push_back(this->_body.get());
}

BinderKindUtils::BoundNodeKind BoundFunctionDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::FunctionDeclaration;
}

std::unique_ptr<BoundBlockStatement> BoundFunctionDeclaration::getBody() {
  return std::move(_body);
}

std::vector<BoundNode *> BoundFunctionDeclaration::getChildren() {
  return this->_children;
}

Utils::FunctionSymbol BoundFunctionDeclaration::getFunctionSymbol() const {
  return _functionSymbol;
}

std::string BoundFunctionDeclaration::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
