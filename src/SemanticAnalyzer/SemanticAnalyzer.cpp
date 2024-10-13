#include "SemanticAnalyzer.h"
#include "BoundStatements/BoundBlockStatement/BoundBlockStatement.h"

std::unique_ptr<BoundGlobalScope> SemanticAnalyzer::analyzeGlobalScope(
    std::unique_ptr<BoundGlobalScope> previousGlobalScope,
    CompilationUnitSyntax *syntax,
    FlowWing::DiagnosticHandler *diagnosticHandler) {

  std::unique_ptr<SyntaxBinder> binder =
      std::make_unique<SyntaxBinder>(nullptr, diagnosticHandler);

  std::unordered_map<std::string, std::any> prevVariablesValues;

  if (previousGlobalScope) {
    binder->getContextRef()->updateBoundScope(previousGlobalScope);
    prevVariablesValues = previousGlobalScope->variablesValues;
  }
  std::unique_ptr<BoundBlockStatement> root(
      static_cast<BoundBlockStatement *>(binder->bind(syntax).release()));

  return std::make_unique<BoundGlobalScope>(
      std::move(previousGlobalScope),
      binder->getContextRef()->getRootRef().get(), prevVariablesValues,
      diagnosticHandler, std::move(root));
}