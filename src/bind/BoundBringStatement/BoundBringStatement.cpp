#include "BoundBringStatement.h"

BoundBringStatement::BoundBringStatement(
    const DiagnosticUtils::SourceLocation &location,
    DiagnosticHandler *diagnosticHandler,
    std::unique_ptr<BoundScopeGlobal> globalScope)
    : BoundSourceLocation(location) {
  this->_diagnosticHandler = diagnosticHandler;
  this->_globalScope = std::move(globalScope);

  for (auto &boundStatement :
       this->_globalScope.get()->globalStatement->getStatements()) {
    this->_children.push_back(boundStatement.get());
  }
}

BinderKindUtils::BoundNodeKind BoundBringStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BringStatement;
}

std::vector<BoundNode *> BoundBringStatement::getChildren() {
  return this->_children;
}

DiagnosticHandler *BoundBringStatement::getDiagnosticHandlerPtr() const {
  return this->_diagnosticHandler;
}

const std::unique_ptr<BoundScopeGlobal> &
BoundBringStatement::getGlobalScopePtr() const {
  return this->_globalScope;
}