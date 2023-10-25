#include "BoundBringStatement.h"

BoundBringStatement::BoundBringStatement(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<CompilationUnitSyntax> compilationUnit,
    std::unique_ptr<DiagnosticHandler> diagnosticHandler,
    std::unique_ptr<BoundScopeGlobal> globalScope)
    : BoundSourceLocation(location) {
  this->_compilationUnit = std::move(compilationUnit);
  this->_diagnosticHandler = std::move(diagnosticHandler);
  this->_globalScope = std::move(globalScope);
}

BinderKindUtils::BoundNodeKind BoundBringStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BringStatement;
}

std::vector<BoundNode *> BoundBringStatement::getChildren() {
  return this->_children;
}

const std::unique_ptr<CompilationUnitSyntax> &
BoundBringStatement::getCompilationUnitPtr() const {
  return this->_compilationUnit;
}

const std::unique_ptr<DiagnosticHandler> &
BoundBringStatement::getDiagnosticHandlerPtr() const {
  return this->_diagnosticHandler;
}

const std::unique_ptr<BoundScopeGlobal> &
BoundBringStatement::getGlobalScopePtr() const {
  return this->_globalScope;
}