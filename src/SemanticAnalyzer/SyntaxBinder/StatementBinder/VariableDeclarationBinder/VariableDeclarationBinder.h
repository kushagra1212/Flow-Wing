#pragma once

#include "../../../../syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "../../../BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../../BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "../StatementBinder.h"

class VariableDeclarationBinder : public StatementBinder {
  std::string _className = "";

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);

  void setClassName(const std::string &className);
};