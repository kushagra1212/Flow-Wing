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


#include "src/common/types/ClassType/ClassType.hpp"

namespace flow_wing {
namespace types {

ClassType::ClassType(const std::string &name,
                     std::shared_ptr<ClassType> base_class)
    : Type(name, TypeKind::kClass), m_base_class(std::move(base_class)) {}

bool ClassType::defineMember(std::shared_ptr<analysis::Symbol> member) {
  return m_members.emplace(member->getName(), std::move(member)).second;
}

std::shared_ptr<analysis::Symbol>
ClassType::lookupMember(const std::string &name) const {
  auto it = m_members.find(name);
  if (it != m_members.end()) {
    return it->second;
  }

  if (m_base_class) {
    return m_base_class->lookupMember(name);
  }

  return nullptr; // Not found
}

std::shared_ptr<ClassType> ClassType::getBaseClass() const {
  return m_base_class;
}

} // namespace types
} // namespace flow_wing