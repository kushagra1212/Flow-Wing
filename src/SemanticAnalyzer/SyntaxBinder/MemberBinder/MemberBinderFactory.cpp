
#include "MemberBinderFactory.h"

#include "FunctionDeclarationBinder/FunctionDeclarationBinder.h"
#include "GlobalStatementBinder/GlobalStatementBinder.h"

std::unique_ptr<MemberBinder>
MemberBinderFactory::create(const SyntaxKindUtils::SyntaxKind &kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax: {
    return std::make_unique<FunctionDeclarationBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::GlobalStatement: {
    return std::make_unique<GlobalStatementBinder>();
  }
  default:
    break;
  }

  assert("Unexpected syntax kind for member binder" && false);

  return nullptr;
}