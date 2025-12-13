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

#include "BoundTernaryExpression.h"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include <cstdlib>
#include <iostream>

namespace flow_wing {
namespace binding {

BoundTernaryExpression::BoundTernaryExpression(
    std::unique_ptr<BoundExpression> condition_expression,
    std::unique_ptr<BoundExpression> true_expression,
    std::unique_ptr<BoundExpression> false_expression,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location),
      m_conditionExpression(std::move(condition_expression)),
      m_trueExpression(std::move(true_expression)),
      m_falseExpression(std::move(false_expression)) {}

NodeKind BoundTernaryExpression::getKind() const {
  return NodeKind::kTernaryExpression;
}

void BoundTernaryExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundTernaryExpression::getType() const {
  return m_trueExpression->getType();
}

const std::unique_ptr<BoundExpression> &
BoundTernaryExpression::getConditionExpression() {

  return std::move(m_conditionExpression);
}

const std::unique_ptr<BoundExpression> &
BoundTernaryExpression::getTrueExpression() {
  return std::move(m_trueExpression);
}

const std::unique_ptr<BoundExpression> &
BoundTernaryExpression::getFalseExpression() {
  return std::move(m_falseExpression);
}

} // namespace binding
} // namespace flow_wing