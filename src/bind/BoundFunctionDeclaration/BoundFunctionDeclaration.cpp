#include "BoundFunctionDeclaration.h"

BoundFunctionDeclaration::BoundFunctionDeclaration(
    const std::string &lineAndColumn,

    Utils::FunctionSymbol functionSymbol, BoundBlockStatement *body)
    : functionSymbol(functionSymbol), body(body) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundFunctionDeclaration::getKind() {
  return BinderKindUtils::BoundNodeKind::FunctionDeclaration;
}

std::vector<BoundNode *> BoundFunctionDeclaration::getChildren() {
  return std::vector<BoundNode *>({body});
}

BoundBlockStatement *BoundFunctionDeclaration::getBody() const { return body; }

Utils::FunctionSymbol BoundFunctionDeclaration::getFunctionSymbol() const {
  return functionSymbol;
}

std::string BoundFunctionDeclaration::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundFunctionDeclaration::~BoundFunctionDeclaration() {
  if (body != nullptr) {
    delete body;
    body = nullptr;
  }
}
