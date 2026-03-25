/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include <string>

namespace flow_wing {
namespace syntax {

class StringLiteralExpressionSyntax : public ExpressionSyntax {

public:
  StringLiteralExpressionSyntax(const SyntaxToken *token);

  /// Same as string literal, but value may differ from the token (e.g. `bring
  /// foo` → synthetic path `foo-module.fg` with the identifier token for spans).
  StringLiteralExpressionSyntax(const SyntaxToken *token, std::string value);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;
  // Getters
  const std::string &getValue() const { return m_value; }

private:
  const SyntaxToken *m_token;
  std::string m_value;
  mutable std::vector<const SyntaxNode *> m_children;
};
} // namespace syntax
} // namespace flow_wing
