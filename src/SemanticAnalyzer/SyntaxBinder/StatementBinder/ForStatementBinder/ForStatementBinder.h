#pragma once

#include "../../../../syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "../../../BoundStatements/BoundForStatement/BoundForStatement.h"
#include "../StatementBinder.h"

class ForStatementBinder : public StatementBinder {

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};