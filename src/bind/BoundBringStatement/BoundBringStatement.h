#ifndef BIND_BRING_STATEMENT_H
#define BIND_BRING_STATEMENT_H

#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../syntax/CompilationUnitSyntax.h"
#include "../Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundBringStatement : public BoundStatement, public BoundSourceLocation {
  FLowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundScopeGlobal> _globalScope;
  std::unordered_map<std::string, int8_t> _expressionStringsMap;

public:
  BoundBringStatement(const DiagnosticUtils::SourceLocation &location,
                      FLowWing::DiagnosticHandler *diagnosticHandler,
                      std::unique_ptr<BoundScopeGlobal> globalScope,
                      std::vector<std::string> &expressionStrings);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
  FLowWing::DiagnosticHandler *getDiagnosticHandlerPtr() const;
  const std::unique_ptr<BoundScopeGlobal> &getGlobalScopePtr() const;

  auto inline isImported(const std::string &name) -> bool {
    return _expressionStringsMap.find(name) != _expressionStringsMap.end();
  }
  auto inline isChoosyImport() -> bool {
    return _expressionStringsMap.size() > 0;
  }
};

#endif // BIND_BRING_STATEMENT_H
