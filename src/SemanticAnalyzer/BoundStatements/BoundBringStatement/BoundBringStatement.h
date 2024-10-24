#ifndef BIND_BRING_STATEMENT_H
#define BIND_BRING_STATEMENT_H

#include "../../../SemanticAnalyzer/SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "../../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../../syntax/CompilationUnitSyntax.h"
#include "../../BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"

class BoundBringStatement : public BoundStatement, public BoundSourceLocation {
  FlowWing::DiagnosticHandler *_diagnosticHandler;
  std::unique_ptr<BoundGlobalScope> _globalScope;
  std::unordered_map<std::string,
                     std::unique_ptr<BoundLiteralExpression<std::any>>>
      _expressionMap;

  std::vector<std::string> _expressionStrings;
  std::string _rootCallerName;

  bool _isModuleImport = false;
  bool _isAlreadyImported = false;

public:
  BoundBringStatement(const DiagnosticUtils::SourceLocation &location,
                      FlowWing::DiagnosticHandler *diagnosticHandler);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;
  FlowWing::DiagnosticHandler *getDiagnosticHandlerPtr() const;
  const std::unique_ptr<BoundGlobalScope> &getGlobalScopePtr() const;

  auto inline setGlobalScope(std::unique_ptr<BoundGlobalScope> globalScope)
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

  inline auto setIsAlreadyImported(bool isAlreadyImported) -> void {
    _isAlreadyImported = isAlreadyImported;
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

  inline auto isAlreadyImported() -> bool { return _isAlreadyImported; }
};

#endif // BIND_BRING_STATEMENT_H
