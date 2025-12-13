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

#include "src/SemanticAnalyzer/BoundNode.hpp"
#include <memory>
#include <vector>

namespace flow_wing {
namespace types {
class Type;
} // namespace types

namespace visitor {
class BoundTreeVisitor;
} // namespace visitor

namespace analysis {
class Symbol;
} // namespace analysis

namespace binding {
class BoundExpression : public BoundNode {
public:
  virtual ~BoundExpression() = default;

  virtual std::shared_ptr<types::Type> getType() const;
  virtual std::vector<std::shared_ptr<types::Type>> getMultipleTypes() const;
  virtual bool isMultipleType() const;
  virtual void accept(visitor::BoundTreeVisitor *visitor) = 0;

protected:
  explicit BoundExpression(
      const flow_wing::diagnostic::SourceLocation &location)
      : BoundNode(location) {}

  BoundExpression() = default;
};
} // namespace binding
} // namespace flow_wing