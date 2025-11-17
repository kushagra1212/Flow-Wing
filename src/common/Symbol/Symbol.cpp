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


#include "Symbol.hpp"
#include "src/common/types/Type.hpp"

namespace flow_wing {
namespace analysis {

Symbol::Symbol(std::string name, SymbolKind kind,
               std::shared_ptr<types::Type> type)
    : m_name(std::move(name)), m_kind(kind), m_type(std::move(type)) {}

// Setters

void Symbol::setIsExposed(bool is_exposed) const { m_is_exposed = is_exposed; }

// Getters

SymbolKind Symbol::getKind() const { return m_kind; }
const std::string &Symbol::getName() const { return m_name; }
std::shared_ptr<types::Type> Symbol::getType() const { return m_type; }
bool Symbol::isExposed() const { return m_is_exposed; }

} // namespace analysis
} // namespace flow_wing