#include "BoundCallExpression.h"

BoundCallExpression::BoundCallExpression(
    Utils::FunctionSymbol functionalSymbol,
    const std::vector<BoundExpression *> &arguments) {
  this->functionalSymbol = functionalSymbol;
  this->arguments = arguments;
}

const std::string &BoundCallExpression::getName() const {
  return functionalSymbol.name;
}

Utils::FunctionSymbol BoundCallExpression::getFunctionSymbol() const {
  return functionalSymbol;
}

const std::vector<BoundExpression *> &
BoundCallExpression::getArguments() const {
  return arguments;
}

BinderKindUtils::BoundNodeKind BoundCallExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::CallExpression;
}

const std::type_info &BoundCallExpression::getType() {
  return functionalSymbol.getReturnType();
}

std::vector<BoundNode *> BoundCallExpression::getChildren() {
  std::vector<BoundNode *> children;
  for (auto &argument : arguments) {
    children.push_back(argument);
  }
  return children;
}

BoundCallExpression::~BoundCallExpression() {
  for (auto &argument : arguments) {
    delete argument;
  }
}