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

#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"

class BoundMultipleAssignmentExpression : public BoundExpression {
  std::vector<std::unique_ptr<BoundAssignmentExpression>> _assignmentList;

public:
  BoundMultipleAssignmentExpression(
      const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline virtual const std::type_info &getType() override {
    return typeid(BoundMultipleAssignmentExpression);
  }
  /*
    Setters
  */

  inline auto
  addAssignment(std::unique_ptr<BoundAssignmentExpression> assignment) -> void {
    _assignmentList.push_back(std::move(assignment));
  }

  /*
    Getters
  */

  inline auto getAssignmentListRef() const
      -> const std::vector<std::unique_ptr<BoundAssignmentExpression>> & {
    return _assignmentList;
  }
};
