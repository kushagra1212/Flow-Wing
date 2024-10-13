
#pragma once

#include "../../../syntax/expression/ExpressionSyntax.h"
#include "ExpressionBinder.h"

class ExpressionBinderFactory {
public:
  static std::unique_ptr<ExpressionBinder>
  create(const SyntaxKindUtils::SyntaxKind &kind);
};