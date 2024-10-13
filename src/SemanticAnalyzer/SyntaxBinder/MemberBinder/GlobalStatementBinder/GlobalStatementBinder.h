#pragma once

#include "../../../../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "../../../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../../../BoundStatements/BoundBreakStatement/BoundBreakStatement.h"
#include "../../StatementBinder/StatementBinder.h"
#include "../MemberBinder.h"

class GlobalStatementBinder : public MemberBinder {

public:
  std::unique_ptr<BoundStatement> bindMember(SyntaxBinderContext *ctx,
                                             MemberSyntax *statement);
};