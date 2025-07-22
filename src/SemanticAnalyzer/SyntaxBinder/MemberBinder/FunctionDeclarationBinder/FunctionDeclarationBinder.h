#pragma once

#include "../../../../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../../../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../../../BoundStatements/BoundBreakStatement/BoundBreakStatement.h"
#include "../../StatementBinder/StatementBinder.h"
#include "../MemberBinder.h"
#include <memory>
class FunctionDeclarationBinder : public MemberBinder {
  std::string _prefix = "";

public:
  std::unique_ptr<BoundStatement> bindMember(SyntaxBinderContext *ctx,
                                             MemberSyntax *statement);

  void setPrefix(const std::string &prefix);
  void handleFunctionDefAndDec(SyntaxBinderContext *ctx,
                               FunctionDeclarationSyntax *syntax,
                               BoundFunctionDeclaration *fd);
};