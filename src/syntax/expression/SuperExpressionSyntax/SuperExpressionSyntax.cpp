/*
 * Flow-Wing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "src/syntax/expression/SuperExpressionSyntax/SuperExpressionSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"

namespace flow_wing {
namespace syntax {

SuperExpressionSyntax::SuperExpressionSyntax(const SyntaxToken *super_keyword_token)
    : m_token(super_keyword_token) {}

NodeKind SuperExpressionSyntax::getKind() const {
  return NodeKind::kSuperExpression;
}

void SuperExpressionSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
SuperExpressionSyntax::getChildren() const {
  if (m_children.empty()) {
    if (m_token)
      m_children.push_back(m_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing
