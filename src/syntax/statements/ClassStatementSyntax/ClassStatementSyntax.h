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

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>

namespace flow_wing {

namespace syntax {

class ClassStatementSyntax : public StatementSyntax {

public:
  ClassStatementSyntax(
      const SyntaxToken *class_keyword_token,
      std::unique_ptr<ExpressionSyntax> class_name_identifier_expr,
      const SyntaxToken *extends_keyword_token,
      std::unique_ptr<ExpressionSyntax> parent_class_identifier_expr,
      const SyntaxToken *open_brace_token,
      std::vector<std::unique_ptr<StatementSyntax>> class_member_statements,
      const SyntaxToken *close_brace_token);

  // Overrides
  NodeKind getKind() const override;
  const std::vector<const SyntaxNode *> &getChildren() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters
  const std::unique_ptr<ExpressionSyntax> &getClassNameIdentifierExpr() const;
  const std::unique_ptr<ExpressionSyntax> &getParentClassIdentifierExpr() const;
  const std::vector<std::unique_ptr<StatementSyntax>> &
  getClassMemberStatements() const;

private:
  const SyntaxToken *m_class_keyword_token;
  std::unique_ptr<ExpressionSyntax> m_class_name_identifier_expr;
  const SyntaxToken *m_extends_keyword_token;
  std::unique_ptr<ExpressionSyntax> m_parent_class_identifier_expr;
  const SyntaxToken *m_open_brace_token;
  std::vector<std::unique_ptr<StatementSyntax>> m_class_member_statements;
  const SyntaxToken *m_close_brace_token;

  mutable std::vector<const SyntaxNode *> m_children;
};

} // namespace syntax

} // namespace flow_wing