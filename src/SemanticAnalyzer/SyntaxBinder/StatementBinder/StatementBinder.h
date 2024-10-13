#pragma once

#include "../../../syntax/statements/StatementSyntax.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"
#include "../ExpressionBinder/ExpressionBinderFactory.h"
#include "../SyntaxBinderContext/SyntaxBinderContext.h"
#include "StatementBinderFactory.h"

class StatementBinder {
public:
  virtual ~StatementBinder() = default;
  virtual std::unique_ptr<BoundStatement>
  bindStatement(SyntaxBinderContext *ctx, StatementSyntax *statement) = 0;
};