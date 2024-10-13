#pragma once

#include "../../../../syntax/statements/ExpressionStatementSyntax/ExpressionStatementSyntax.h"
#include "../../../BoundStatements/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../StatementBinder.h"

class ExpressionStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};