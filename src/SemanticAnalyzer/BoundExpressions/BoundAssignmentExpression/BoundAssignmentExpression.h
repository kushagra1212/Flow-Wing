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

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"

namespace flow_wing {
namespace binding {

class BoundAssignmentExpression : public BoundExpression {

public:
  BoundAssignmentExpression(
      std::vector<std::unique_ptr<BoundExpression>> left,
      std::vector<std::unique_ptr<BoundExpression>> right,
      bool is_full_re_assignment,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundAssignmentExpression() = default;

  // Overrides
  NodeKind getKind() const override;

  // Getters
  std::shared_ptr<types::Type> getType() const override;
  bool isMultiTargetAssignment() const;

private:
  std::vector<std::unique_ptr<BoundExpression>> m_left;
  std::vector<std::unique_ptr<BoundExpression>> m_right;
  [[maybe_unused]] bool m_is_full_re_assignment;
};
} // namespace binding
} // namespace flow_wing