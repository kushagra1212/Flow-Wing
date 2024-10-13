#pragma once

#include "../../../../syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "../../../BoundStatements/BoundOrIfStatement/BoundOrIfStatement.h"
#include "../StatementBinder.h"

class OrIfStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};