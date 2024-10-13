#pragma once

#include "../../../syntax/MemberSyntax.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"
#include "../ExpressionBinder/ExpressionBinderFactory.h"
#include "../SyntaxBinderContext/SyntaxBinderContext.h"

class MemberBinder {
public:
  virtual ~MemberBinder() = default;
  virtual std::unique_ptr<BoundStatement> bindMember(SyntaxBinderContext *ctx,
                                                     MemberSyntax *syntax) = 0;
};