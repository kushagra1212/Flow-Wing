#pragma once

#include "../../../../syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "../../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../../MemberBinder/FunctionDeclarationBinder/FunctionDeclarationBinder.h"
#include "../StatementBinder.h"
#include "../VariableDeclarationBinder/VariableDeclarationBinder.h"
#include <memory>
class ClassStatementBinder : public StatementBinder {
public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};