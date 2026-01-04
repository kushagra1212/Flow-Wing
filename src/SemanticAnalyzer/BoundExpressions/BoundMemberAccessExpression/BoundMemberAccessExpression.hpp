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
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"

namespace flow_wing {
namespace binding {

class BoundMemberAccessExpression : public BoundExpression {

public:
  BoundMemberAccessExpression(
      std::unique_ptr<BoundExpression> left_expression,
      const std::string &member_name, std::shared_ptr<types::Type> field_type,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundMemberAccessExpression() = default;

  // Overrides
  NodeKind getKind() const override;
  std::shared_ptr<types::Type> getType() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;

  // Getters
  const std::unique_ptr<BoundExpression> &getLeftExpression() const;
  std::string getMemberName() const;

private:
  std::unique_ptr<BoundExpression> m_left_expression;
  std::string m_member_name;
  std::shared_ptr<types::Type> m_field_type;
};
} // namespace binding
} // namespace flow_wing