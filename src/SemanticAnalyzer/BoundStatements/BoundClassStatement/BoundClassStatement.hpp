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

#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <vector>
#include <memory>

namespace flow_wing {
namespace binding {

class BoundClassStatement : public BoundStatement {

public:
  BoundClassStatement(
      std::shared_ptr<analysis::Symbol> class_symbol,
      std::vector<std::unique_ptr<BoundStatement>> class_member_statements,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundClassStatement() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters

private:
  std::shared_ptr<analysis::Symbol> m_class_symbol;
  std::vector<std::unique_ptr<BoundStatement>> m_class_member_statements;
};
} // namespace binding
} // namespace flow_wing