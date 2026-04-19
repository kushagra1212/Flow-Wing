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


#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

std::string BoundTreeJson::getShortId(const void *ptr) {
  if (m_ptr_to_id_map.find(ptr) == m_ptr_to_id_map.end()) {
    m_ptr_to_id_map[ptr] = m_next_id++;
  }

  size_t id = m_ptr_to_id_map[ptr];

  std::stringstream ss;
  ss << "0x" << std::uppercase << std::hex << id;
  return ss.str();
}

} // namespace flow_wing::compiler::serializer