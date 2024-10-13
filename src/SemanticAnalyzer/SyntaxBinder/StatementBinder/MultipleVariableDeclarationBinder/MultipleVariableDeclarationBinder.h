#pragma once

#include "../../../../syntax/statements/MultipleVariableDeclarationSyntax/MultipleVariableDeclarationSyntax.h"
#include "../../../BoundStatements/BoundMultipleVariableDeclaration/BoundMultipleVariableDeclaration.h"
#include "../StatementBinder.h"

class MultipleVariableDeclarationBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};