#pragma once

#include "../../../../syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "../../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../StatementBinder.h"

class BlockStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};