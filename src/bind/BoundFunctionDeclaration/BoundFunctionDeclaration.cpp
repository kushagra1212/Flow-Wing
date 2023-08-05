#include "BoundFunctionDeclaration.h"

BoundFunctionDeclaration::BoundFunctionDeclaration(
    Utils::FunctionSymbol functionSymbol, BoundBlockStatement *body)
    : functionSymbol(functionSymbol), body(body) {}

BoundFunctionDeclaration::~BoundFunctionDeclaration() { delete body; }

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
