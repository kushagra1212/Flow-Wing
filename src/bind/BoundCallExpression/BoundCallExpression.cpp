#include "BoundCallExpression.h"

BoundCallExpression::BoundCallExpression(
    BoundLiteralExpression<std::any> *callerIdentifier,
    Utils::FunctionSymbol functionalSymbol,
    const std::vector<BoundExpression *> &arguments,
    const std::string &lineAndColumn) {
  this->functionalSymbol = functionalSymbol;
  this->arguments = arguments;
  this->_callerIdentifier = callerIdentifier;
  this->_lineAndColumn = lineAndColumn;
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
  children.push_back(_callerIdentifier);
  for (auto &argument : arguments) {
    children.push_back(argument);
  }
  return children;
}

std::string BoundCallExpression::getLineNumberAndPosition() const {
  return this->_lineAndColumn;
}

BoundLiteralExpression<std::any> *
BoundCallExpression::getCallerIdentifier() const {
  return _callerIdentifier;
}

BoundCallExpression::~BoundCallExpression() {
  for (auto &argument : arguments) {
    if (argument != nullptr) {
      delete argument;
      argument = nullptr;
    }
  }
  arguments.clear();
}
