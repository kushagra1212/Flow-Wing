#include "BoundCallExpression.h"

BoundCallExpression::BoundCallExpression(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier,
    Utils::FunctionSymbol functionalSymbol)
    : BoundSourceLocation(location) {
  this->_functionalSymbol = functionalSymbol;
  this->_callerIdentifier = std::move(callerIdentifier);
}

const std::string &BoundCallExpression::getName() const {
  return _functionalSymbol.name;
}

Utils::FunctionSymbol BoundCallExpression::getFunctionSymbol() const {
  return _functionalSymbol;
}

void BoundCallExpression::addArgument(
    std::unique_ptr<BoundExpression> argument) {
  _arguments.push_back(std::move(argument));
}

std::vector<std::unique_ptr<BoundExpression>> &
BoundCallExpression::getArguments() {
  return _arguments;
}

std::unique_ptr<BoundLiteralExpression<std::any>>
BoundCallExpression::getCallerIdentifier() {
  return std::move(_callerIdentifier);
}

const std::type_info &BoundCallExpression::getType() {
  return _functionalSymbol.getReturnType();
}

BinderKindUtils::BoundNodeKind BoundCallExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::CallExpression;
}

std::vector<BoundNode *> BoundCallExpression::getChildren() {

  if (_callerIdentifier != nullptr) {
    this->_children.push_back(_callerIdentifier.get());
    for (auto &argument : _arguments) {
      this->_children.push_back(argument.get());
    }
    return _children;
  }

  return _children;
}

std::unique_ptr<BoundLiteralExpression<std::any>> &
BoundCallExpression::getCallerIdentifierPtr() {
  return _callerIdentifier;
}
