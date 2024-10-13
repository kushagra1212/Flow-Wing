#pragma once

#include "../../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "BoundGlobalScope/BoundGlobalScope.h"
#include "BoundScope/BoundScope.h"
#include "MemberBinder/MemberBinder.h"
#include "SyntaxBinderContext/SyntaxBinderContext.h"
#include <memory>

class SyntaxBinder {
  std::unique_ptr<SyntaxBinderContext> _context = nullptr;

public:
  SyntaxBinder(std::unique_ptr<BoundScope> scope,
               FlowWing::DiagnosticHandler *diagnosticHandler);

  std::unique_ptr<BoundStatement> bind(CompilationUnitSyntax *syntax);

  std::unique_ptr<SyntaxBinderContext> &getContextRef();
};
