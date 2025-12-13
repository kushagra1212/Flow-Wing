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

#include "BoundCallExpression.h"
#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"

namespace flow_wing {
namespace binding {

BoundCallExpression::BoundCallExpression(
    analysis::FunctionSymbol *symbol,
    std::vector<std::unique_ptr<BoundExpression>> arguments,
    const flow_wing::diagnostic::SourceLocation &location)
    : BoundExpression(location), m_symbol(symbol),
      m_arguments(std::move(arguments)) {}

NodeKind BoundCallExpression::getKind() const {
  return NodeKind::kCallExpression;
}

void BoundCallExpression::accept(visitor::BoundTreeVisitor *visitor) {
  visitor->visit(this);
}

std::shared_ptr<types::Type> BoundCallExpression::getType() const {
  return static_cast<types::FunctionType *>(m_symbol->getType().get())
      ->getReturnTypes()[0]
      ->type;
}

bool BoundCallExpression::isMultipleType() const {
  return static_cast<types::FunctionType *>(m_symbol->getType().get())
             ->getReturnTypes()
             .size() > 1;
}

std::vector<std::shared_ptr<types::Type>>
BoundCallExpression::getMultipleTypes() const {
  std::vector<std::shared_ptr<types::Type>> types;
  for (const auto &return_type :
       static_cast<types::FunctionType *>(m_symbol->getType().get())
           ->getReturnTypes()) {
    types.push_back(return_type->type);
  }
  return types;
}

const analysis::FunctionSymbol *BoundCallExpression::getSymbol() const {
  return m_symbol;
}

const std::vector<std::unique_ptr<BoundExpression>> &
BoundCallExpression::getArguments() const {
  return m_arguments;
}

} // namespace binding
} // namespace flow_wing