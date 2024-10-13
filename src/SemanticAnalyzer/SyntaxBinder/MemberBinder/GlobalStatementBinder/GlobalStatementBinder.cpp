
#include "GlobalStatementBinder.h"

std::unique_ptr<BoundStatement>
GlobalStatementBinder::bindMember(SyntaxBinderContext *ctx,
                                  MemberSyntax *statement) {

  GlobalStatementSyntax *syntax =
      static_cast<GlobalStatementSyntax *>(statement);

  return StatementBinderFactory::create(syntax->getStatementPtr()->getKind())
      ->bindStatement(ctx, syntax->getStatementPtr().get());
}
