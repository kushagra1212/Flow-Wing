#pragma once

#include "../../../../syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "../../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../../../BoundStatements/BoundIfStatement/BoundIfStatement.h"
#include "../StatementBinder.h"

class IfStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};