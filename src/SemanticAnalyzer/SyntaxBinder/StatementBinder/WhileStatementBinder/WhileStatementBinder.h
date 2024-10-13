#pragma once

#include "../../../../syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include "../../../BoundStatements/BoundWhileStatement/BoundWhileStatement.h"
#include "../StatementBinder.h"

class WhileStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};