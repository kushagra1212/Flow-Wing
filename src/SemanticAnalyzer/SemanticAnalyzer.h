#pragma once

#include "../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "SyntaxBinder/BoundGlobalScope/BoundGlobalScope.h"
#include "SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "SyntaxBinder/SyntaxBinder.h"

class SemanticAnalyzer {
public:
  static std::unique_ptr<BoundGlobalScope>
  analyzeGlobalScope(std::unique_ptr<BoundGlobalScope> previous,
                     CompilationUnitSyntax *syntax,
                     FlowWing::DiagnosticHandler *diagnosticHandler);
};