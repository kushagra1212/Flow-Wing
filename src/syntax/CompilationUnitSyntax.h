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

#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/SyntaxNode.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>
#include <vector>
namespace flow_wing {
namespace syntax {

enum class NodeKind : int;

class CompilationUnitSyntax : public SyntaxNode {

public:
  CompilationUnitSyntax(
      std::vector<std::unique_ptr<StatementSyntax>> global_statements,
      const SyntaxToken *end_of_file_token);

  // Overrides
  const std::vector<const SyntaxNode *> &getChildren() const override;
  NodeKind getKind() const override;
  void accept(visitor::ASTVisitor *visitor) override;

  // Getters
  const std::vector<std::unique_ptr<StatementSyntax>> &getStatements() const {
    return m_global_statements;
  }

private:
  std::vector<std::unique_ptr<StatementSyntax>> m_global_statements;
  const SyntaxToken *m_end_of_file_token = nullptr;

  mutable std::vector<const SyntaxNode *> m_children;
};

} // namespace syntax
} // namespace flow_wing