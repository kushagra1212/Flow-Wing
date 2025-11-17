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

class BoundNirastLiteralExpression : public BoundExpression {

public:
  BoundNirastLiteralExpression(std::shared_ptr<types::Type> type);
  ~BoundNirastLiteralExpression() = default;

  // Overrides
  NodeKind getKind() const override;

  // Getters
  std::shared_ptr<types::Type> getType() const override;

private:
  std::shared_ptr<types::Type> m_type;
};
} // namespace binding
} // namespace flow_wing