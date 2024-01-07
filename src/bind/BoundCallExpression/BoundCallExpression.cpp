#include "BoundCallExpression.h"

BoundCallExpression::BoundCallExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

void BoundCallExpression::addArgument(
    std::unique_ptr<BoundExpression> argument) {
  _arguments.push_back(std::move(argument));
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundCallExpression::getArgumentsRef() const {
  return _arguments;
}

const std::type_info &BoundCallExpression::getType() {
  return _callerIdentifier->getType();
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

void BoundCallExpression::setCallerIdentifier(
    std::unique_ptr<BoundLiteralExpression<std::any>> callerIdentifier) {
  _callerIdentifier = std::move(callerIdentifier);
  _callerName = std::any_cast<std::string>(_callerIdentifier->getValue());
}
