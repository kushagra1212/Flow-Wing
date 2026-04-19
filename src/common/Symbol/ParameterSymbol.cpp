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


#include "ParameterSymbol.hpp"
#include "FunctionSymbol.hpp"

namespace flow_wing {

namespace analysis {

  ParameterSymbol::ParameterSymbol(
    std::string name, std::shared_ptr<types::Type> type,
    std::unique_ptr<binding::BoundExpression> default_value_expression)
    : Symbol(std::move(name), SymbolKind::kParameter, std::move(type)),
      m_default_value_expression(std::move(default_value_expression)) {
  BINDER_DEBUG_LOG("Creating ParameterSymbol: " + getName(),
                   "ParameterSymbol");

 if(getType()->getKind() == types::TypeKind::kFunction) {
  BINDER_DEBUG_LOG("Creating FunctionSymbol: " + getName(), "FunctionSymbol");
  m_function_symbol = std::make_shared<analysis::FunctionSymbol>(getName(), getType(), true);
 }
}

 const std::unique_ptr<binding::BoundExpression> & ParameterSymbol::getDefaultValueExpression() const {
    return m_default_value_expression;
  }

 const std::shared_ptr<analysis::FunctionSymbol> & ParameterSymbol::getFunctionSymbol() {
    return m_function_symbol;
  }


}}