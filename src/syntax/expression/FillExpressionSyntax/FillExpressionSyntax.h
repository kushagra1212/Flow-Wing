/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

#include "src/syntax/expression/ExpressionSyntax.h"
#include <memory>

namespace flow_wing {
namespace syntax {

class SyntaxToken;

class FillExpressionSyntax : public ExpressionSyntax {

public:
  FillExpressionSyntax(
      const syntax::SyntaxToken *open_bracket,
      std::unique_ptr<ExpressionSyntax> size_to_fill_expression,
      const syntax::SyntaxToken *fill_keyword,
      std::unique_ptr<ExpressionSyntax> element_expression,
      const syntax::SyntaxToken *close_bracket);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters

private:
  const syntax::SyntaxToken *m_open_bracket;
  std::unique_ptr<ExpressionSyntax>
      m_size_to_fill_expression; // number literal expression
  const syntax::SyntaxToken *m_fill_keyword;
  std::unique_ptr<ExpressionSyntax> m_element_expression;
  const syntax::SyntaxToken *m_close_bracket;

  mutable std::vector<const SyntaxNode *> m_children;
};

} // namespace syntax
} // namespace flow_wing