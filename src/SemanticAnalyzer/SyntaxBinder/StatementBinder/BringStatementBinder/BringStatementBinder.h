#pragma once

#include "../../../../syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "../../../../syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "../../../../syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include "../../../BoundStatements/BoundBringStatement/BoundBringStatement.h"
#include "../../../SemanticAnalyzer.h"
#include "../StatementBinder.h"
#include <memory>
class BringStatementBinder : public StatementBinder {

  std::unordered_map<std::string, int>
  getMemberMap(const std::vector<std::unique_ptr<MemberSyntax>> &members,
               CompilationUnitSyntax *nestedCompilationUnit);

public:
  std::unique_ptr<BoundStatement> bindStatement(SyntaxBinderContext *ctx,
                                                StatementSyntax *statement);
};