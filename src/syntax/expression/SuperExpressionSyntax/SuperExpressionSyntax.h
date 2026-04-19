/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * Primary expression `super` (typically followed by `(args)` for base init).
 */

#pragma once

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"

namespace flow_wing {
namespace syntax {

class SuperExpressionSyntax : public ExpressionSyntax {

public:
  explicit SuperExpressionSyntax(const SyntaxToken *super_keyword_token);

  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  const SyntaxToken *getSuperKeywordToken() const { return m_token; }

private:
  const SyntaxToken *m_token;
  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing
