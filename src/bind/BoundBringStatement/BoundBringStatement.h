#ifndef BIND_BRING_STATEMENT_H
#define BIND_BRING_STATEMENT_H

#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../syntax/CompilationUnitSyntax.h"
#include "../Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../BoundLiteralExpression/BoundLiteralExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"
class BoundBringStatement : public BoundStatement, public BoundSourceLocation {
  FLowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundScopeGlobal> _globalScope;
  std::unordered_map<std::string,
                     std::unique_ptr<BoundLiteralExpression<std::any>>>
      _expressionMap;

  std::vector<std::string> _expressionStrings;
  std::string _rootCallerName;

  bool _isModuleImport = false;

public:
  BoundBringStatement(const DiagnosticUtils::SourceLocation &location,
                      FLowWing::DiagnosticHandler *diagnosticHandler);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
  FLowWing::DiagnosticHandler *getDiagnosticHandlerPtr() const;
  const std::unique_ptr<BoundScopeGlobal> &getGlobalScopePtr() const;

  auto inline setGlobalScope(std::unique_ptr<BoundScopeGlobal> globalScope)
      -> void {
    _globalScope = std::move(globalScope);
  }

  inline auto setIsModuleImport(bool isModuleImport) -> void {
    _isModuleImport = isModuleImport;
  }

  auto inline setExpression(
      std::string name,
      std::unique_ptr<BoundLiteralExpression<std::any>> expression) -> void {
    _expressionStrings.push_back(name);
    _expressionMap[name] = std::move(expression);
  }

  auto inline isImported(const std::string &name) -> bool {
    return _expressionMap.find(name) != _expressionMap.end();
  }

  auto inline getExpressionRef(const std::string &name)
      -> std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return _expressionMap[name];
  }

  auto inline getExpressionStrings() -> std::vector<std::string> {

    return _expressionStrings;
  }

  auto inline isChoosyImport() -> bool {
    return _expressionMap.begin() != _expressionMap.end();
  }

  auto inline setRootCallerName(const std::string &name) -> void {
    _rootCallerName = name;
  }

  auto inline getRootCallerName() -> std::string { return _rootCallerName; }

  inline auto isModuleImport() -> bool { return _isModuleImport; }
};

#endif // BIND_BRING_STATEMENT_H
