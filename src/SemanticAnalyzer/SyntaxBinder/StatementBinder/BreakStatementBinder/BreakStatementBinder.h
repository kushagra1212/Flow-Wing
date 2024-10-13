#pragma once

#include "../../../../syntax/statements/BreakStatementSyntax/BreakStatementSyntax.h"
#include "../../../BoundStatements/BoundBreakStatement/BoundBreakStatement.h"
#include "../StatementBinder.h"

class BreakStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};