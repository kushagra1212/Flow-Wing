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
#include <map>
namespace flow_wing {
namespace binding {

class BoundObjectExpression : public BoundExpression {

public:
  BoundObjectExpression(
      std::map<std::string, std::shared_ptr<types::Type>> field_types_map,
      std::vector<std::unique_ptr<BoundExpression>> colon_expressions,
      std::shared_ptr<types::Type> type,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundObjectExpression() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters
  std::shared_ptr<types::Type> getType() const override;
  void setType(std::shared_ptr<types::Type> type);

  const std::map<std::string, std::shared_ptr<types::Type>> &
  getFieldTypesMap() const;
  const std::vector<std::unique_ptr<BoundExpression>> &
  getColonExpressions() const;

private:
  std::map<std::string, std::shared_ptr<types::Type>> m_field_types_map;
  std::vector<std::unique_ptr<BoundExpression>> m_colon_expressions;
  std::shared_ptr<types::Type> m_type;
};
} // namespace binding
} // namespace flow_wing