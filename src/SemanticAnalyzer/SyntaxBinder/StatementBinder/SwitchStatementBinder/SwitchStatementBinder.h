#pragma once

#include "../../../../syntax/statements/SwitchStatementSyntax/SwitchStatementSyntax.h"
#include "../../../BoundStatements/BoundSwitchStatement/BoundSwitchStatement.h"
#include "../CaseStatementBinder/CaseStatementBinder.h"
#include "../StatementBinder.h"

class SwitchStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};