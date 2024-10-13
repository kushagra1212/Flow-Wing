#pragma once

#include "../../../../syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "../../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../StatementBinder.h"

class CustomTypeStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};