#ifndef BIND_BRING_STATEMENT_H
#define BIND_BRING_STATEMENT_H

#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../syntax/CompilationUnitSyntax.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundBringStatement : public BoundStatement, public BoundSourceLocation {
  std::unique_ptr<CompilationUnitSyntax> _compilationUnit;
  std::unique_ptr<DiagnosticHandler> _diagnosticHandler;

public:
  BoundBringStatement(const DiagnosticUtils::SourceLocation &location,
                      std::unique_ptr<CompilationUnitSyntax> compilationUnit,
                      std::unique_ptr<DiagnosticHandler> diagnosticHandler);

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  const std::unique_ptr<CompilationUnitSyntax> &getCompilationUnitPtr() const;
  const std::unique_ptr<DiagnosticHandler> &getDiagnosticHandlerPtr() const;
};

#endif // BIND_BRING_STATEMENT_H