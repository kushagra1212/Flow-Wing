#pragma once

#include "../../../../syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "../../../BoundStatements/BoundCaseStatement/BoundCaseStatement.h"
#include "../StatementBinder.h"

class CaseStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};