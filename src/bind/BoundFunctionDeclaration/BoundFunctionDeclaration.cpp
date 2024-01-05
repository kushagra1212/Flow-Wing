#include "BoundFunctionDeclaration.h"

BoundFunctionDeclaration::BoundFunctionDeclaration(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind BoundFunctionDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::FunctionDeclaration;
}

std::vector<BoundNode *> BoundFunctionDeclaration::getChildren() {
  if (this->_children.size() == 0) {
    this->_children.push_back(this->_body.get());
    for (const auto &parameter : this->_parameters) {
      this->_children.push_back(parameter.get());
    }
  }

  return this->_children;
}

void BoundFunctionDeclaration::addParameter(
    std::unique_ptr<BoundVariableExpression> parameter) {
  this->_parameters.push_back(std::move(parameter));
}

void BoundFunctionDeclaration::setFunctionName(
    const std::string &functionName) {
  this->_functionName = functionName;
}

void BoundFunctionDeclaration::setFunctionBody(
    std::unique_ptr<BoundBlockStatement> body) {
  this->_body = std::move(body);
}
