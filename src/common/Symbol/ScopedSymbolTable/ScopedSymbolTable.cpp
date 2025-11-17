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


#include "ScopedSymbolTable.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"

namespace flow_wing {
namespace analysis {

ScopedSymbolTable::ScopedSymbolTable() {
  // entering the global scope
  enterScope();
}

void ScopedSymbolTable::enterScope() {
  m_scope_stack.emplace_back(std::make_unique<SymbolTable>());
}

void ScopedSymbolTable::leaveScope() {
  if (m_scope_stack.size() > 1) { // not popping the global scope
    m_scope_stack.pop_back();
  }
}

bool ScopedSymbolTable::define(std::shared_ptr<Symbol> symbol) {
  auto &current_scope = *m_scope_stack.back();
  auto [it, inserted] = current_scope.try_emplace(symbol->getName(), symbol);
  return inserted;
}

bool ScopedSymbolTable::isInBreakScope() const {
  return m_scope_stack.back()->size() > 1;
}

bool ScopedSymbolTable::isInReturnScope() const {
  return m_current_function_symbol != nullptr;
}

void ScopedSymbolTable::setCurrentFunctionSymbol(
    const FunctionSymbol *function) {
  m_current_function_symbol = function;
}

const FunctionSymbol *ScopedSymbolTable::getCurrentFunctionSymbol() const {
  return m_current_function_symbol;
}

std::shared_ptr<Symbol>
ScopedSymbolTable::lookup(const std::string &name) const {
  // iterating from the top of the stack (current scope) down to the bottom
  // (global scope)
  for (auto it = m_scope_stack.rbegin(); it != m_scope_stack.rend(); ++it) {
    auto &scope = **it;
    if (auto symbol_it = scope.find(name); symbol_it != scope.end()) {
      return symbol_it->second;
    }
  }
  return nullptr;
}

} // namespace analysis
} // namespace flow_wing