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
#include "src/common/types/ArrayType/ArrayType.hpp"

#include <deque>
namespace flow_wing {
namespace binding {

class BoundContainerExpressionElement {
public:
  BoundContainerExpressionElement(std::unique_ptr<BoundExpression> expression);
  ~BoundContainerExpressionElement() = default;

  void addIndex(size_t index);
  const std::deque<size_t> &getIndices() const;
  std::unique_ptr<BoundExpression> &getExpression();

private:
  std::deque<size_t> m_indices;
  std::unique_ptr<BoundExpression> m_expression;
};

class BoundContainerExpression : public BoundExpression {

public:
  BoundContainerExpression(
      std::vector<std::unique_ptr<BoundContainerExpressionElement>> elements,
      std::shared_ptr<types::ArrayType> type, bool is_default_value,
      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundContainerExpression() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;
  // Getters
  std::shared_ptr<types::Type> getType() const override;

  std::vector<std::unique_ptr<BoundContainerExpressionElement>> &getElements();
  bool isDefaultValue() const;

private:
  std::vector<std::unique_ptr<BoundContainerExpressionElement>> m_elements;
  std::shared_ptr<types::ArrayType> m_type;
  bool m_is_default_value;
};
} // namespace binding
} // namespace flow_wing