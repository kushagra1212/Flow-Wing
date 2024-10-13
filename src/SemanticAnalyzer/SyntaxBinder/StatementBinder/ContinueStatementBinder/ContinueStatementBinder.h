#pragma once

#include "../../../../syntax/statements/ContinueStatementSyntax/ContinueStatementSyntax.h"
#include "../../../BoundStatements/BoundContinueStatement/BoundContinueStatement.h"
#include "../StatementBinder.h"

class ContinueStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};