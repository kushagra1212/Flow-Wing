#include "BoundBringStatement.h"

BoundBringStatement::BoundBringStatement(
    const DiagnosticUtils::SourceLocation &location,
    FlowWing::DiagnosticHandler *diagnosticHandler)
    : BoundSourceLocation(location) {
  this->_diagnosticHandler = diagnosticHandler;
}

BinderKindUtils::BoundNodeKind BoundBringStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BringStatement;
}

std::vector<BoundNode *> BoundBringStatement::getChildren() {
  if (this->_children.empty()) {
    if (this->_globalScope) {
      for (auto &boundStatement :
           this->_globalScope.get()->globalStatement->getStatements()) {
        this->_children.push_back(boundStatement.get());
      }
    }
  }
  return this->_children;
}

FlowWing::DiagnosticHandler *
BoundBringStatement::getDiagnosticHandlerPtr() const {
  return this->_diagnosticHandler;
}

const std::unique_ptr<BoundGlobalScope> &
BoundBringStatement::getGlobalScopePtr() const {
  return this->_globalScope;
}