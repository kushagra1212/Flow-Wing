#pragma once

#include "../../../../syntax/statements/ReturnStatementSyntax/ReturnStatementSyntax.h"
#include "../../../BoundStatements/BoundReturnStatement/BoundReturnStatement.h"
#include "../StatementBinder.h"

class ReturnStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};