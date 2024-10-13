
#pragma once

#include "../../../syntax/statements/StatementSyntax.h"

class StatementBinder;

class StatementBinderFactory {
public:
  static std::unique_ptr<StatementBinder>
  create(const SyntaxKindUtils::SyntaxKind &kind);
};
