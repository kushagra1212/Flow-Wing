

#pragma once

#include "../../../syntax/statements/StatementSyntax.h"
#include "MemberBinder.h"

class MemberBinder;

class MemberBinderFactory {
public:
  static std::unique_ptr<MemberBinder>
  create(const SyntaxKindUtils::SyntaxKind &kind);
};
