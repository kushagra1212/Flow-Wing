#include "BoundCallExpression.h"

BoundCallExpression::BoundCallExpression(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundLiteralExpression<std::any>> callerIdentifier,
    Utils::FunctionSymbol functionalSymbol,
    const std::vector<std::shared_ptr<BoundExpression>> &arguments) {
  this->_functionalSymbol = functionalSymbol;
  this->_arguments = arguments;
  this->_callerIdentifier = callerIdentifier;
  this->_lineAndColumn = lineAndColumn;
}

const std::string &BoundCallExpression::getName() const {
  return _functionalSymbol.name;
}

Utils::FunctionSymbol BoundCallExpression::getFunctionSymbol() const {
  return _functionalSymbol;
}

const std::vector<std::shared_ptr<BoundExpression>> &
BoundCallExpression::getArguments() const {
  return _arguments;
}

BinderKindUtils::BoundNodeKind BoundCallExpression::getKind() {
  return BinderKindUtils::BoundNodeKind::CallExpression;
}

const std::type_info &BoundCallExpression::getType() {
  return _functionalSymbol.getReturnType();
}

std::vector<std::shared_ptr<BoundNode>> BoundCallExpression::getChildren() {
  std::vector<std::shared_ptr<BoundNode>> children;
  children.push_back(_callerIdentifier);
  for (auto &argument : _arguments) {
    children.push_back(argument);
  }
  return children;
}

std::string BoundCallExpression::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

std::shared_ptr<BoundLiteralExpression<std::any>>
BoundCallExpression::getCallerIdentifier() const {
  return _callerIdentifier;
}
