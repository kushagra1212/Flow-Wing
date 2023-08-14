#include "BoundFunctionDeclaration.h"

BoundFunctionDeclaration::BoundFunctionDeclaration(
    const std::string &lineAndColumn,

    Utils::FunctionSymbol functionSymbol,
    std::shared_ptr<BoundBlockStatement> body)
    : _functionSymbol(functionSymbol), _body(body) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundFunctionDeclaration::getKind() {
  return BinderKindUtils::BoundNodeKind::FunctionDeclaration;
}

std::vector<std::shared_ptr<BoundNode>>
BoundFunctionDeclaration::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>({_body});
}

std::shared_ptr<BoundBlockStatement> BoundFunctionDeclaration::getBody() const {
  return _body;
}

Utils::FunctionSymbol BoundFunctionDeclaration::getFunctionSymbol() const {
  return _functionSymbol;
}

std::string BoundFunctionDeclaration::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
