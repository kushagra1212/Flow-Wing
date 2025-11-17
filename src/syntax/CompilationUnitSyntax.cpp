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

#include "CompilationUnitSyntax.h"
#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/syntax/SyntaxToken.h"

namespace flow_wing {
namespace syntax {

CompilationUnitSyntax::CompilationUnitSyntax(
    std::vector<std::unique_ptr<StatementSyntax>> global_statements,
    const SyntaxToken *end_of_file_token)
    : m_global_statements(std::move(global_statements)),
      m_end_of_file_token(end_of_file_token) {}

NodeKind CompilationUnitSyntax::getKind() const {
  return NodeKind::kCompilationUnit;
}

void CompilationUnitSyntax::accept(visitor::ASTVisitor *visitor) {
  visitor->visit(this);
}

const std::vector<const SyntaxNode *> &
CompilationUnitSyntax::getChildren() const {
  if (m_children.empty()) {
    for (const auto &global_statement : m_global_statements) {
      if (global_statement)
        m_children.emplace_back(global_statement.get());
    }
    if (m_end_of_file_token)
      m_children.emplace_back(m_end_of_file_token);
  }
  return m_children;
}

} // namespace syntax
} // namespace flow_wing
