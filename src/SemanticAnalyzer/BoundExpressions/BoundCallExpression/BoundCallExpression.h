/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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
#include <cstddef>
#include <memory>
#include <vector>

namespace flow_wing {
namespace analysis {
class FunctionSymbol;
} // namespace analysis
namespace binding {

class BoundCallExpression : public BoundExpression {

public:
  BoundCallExpression(analysis::FunctionSymbol *symbol,
                      std::vector<std::unique_ptr<BoundExpression>> arguments,
                      const flow_wing::diagnostic::SourceLocation &location);
  ~BoundCallExpression() = default;

  // Overrides
  NodeKind getKind() const override;
  void accept(visitor::BoundTreeVisitor *visitor) override;

  // Getters
  std::shared_ptr<types::Type> getType() const override;
  bool isMultipleType() const override;
  std::vector<std::shared_ptr<types::Type>> getMultipleTypes() const override;
  const analysis::FunctionSymbol *getSymbol() const;

  const std::vector<std::unique_ptr<BoundExpression>> &getArguments() const;

  bool getUseVirtualDispatch() const { return m_use_virtual_dispatch; }
  std::size_t getVirtualSlot() const { return m_virtual_slot; }
  void setVirtualDispatch(bool use, std::size_t slot) {
    m_use_virtual_dispatch = use;
    m_virtual_slot = slot;
  }

  void setImplicitReceiverLast(bool v) { m_implicit_receiver_last = v; }
  bool getImplicitReceiverLast() const { return m_implicit_receiver_last; }

private:
  analysis::FunctionSymbol *m_symbol;
  std::vector<std::unique_ptr<BoundExpression>> m_arguments;
  bool m_use_virtual_dispatch = false;
  std::size_t m_virtual_slot = 0;
  bool m_implicit_receiver_last = false;
};
} // namespace binding
} // namespace flow_wing