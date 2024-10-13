#pragma once

#include "../../../../syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "../../../../syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "../../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../../MemberBinder/FunctionDeclarationBinder/FunctionDeclarationBinder.h"
#include "../StatementBinder.h"
#include "../VariableDeclarationBinder/VariableDeclarationBinder.h"

class ModuleStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};