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

#include "src/common/types/ArrayType/ArrayType.hpp"
#include <sstream>

namespace flow_wing {
namespace types {

ArrayType::ArrayType(std::shared_ptr<Type> underlying_type,
                     const std::vector<size_t> &dimensions)
    : Type(buildArrayTypeName(underlying_type, dimensions), TypeKind::kArray),
      m_underlying_type(std::move(underlying_type)), m_dimensions(dimensions) {}

bool ArrayType::operator==(const Type &other) const {
  if (other.getKind() != TypeKind::kArray) {
    return false;
  }

  const auto *other_array = static_cast<const ArrayType *>(&other);

  if ((*m_underlying_type != *other_array->m_underlying_type)) {
    return false;
  }

  if (m_dimensions.size() != other_array->m_dimensions.size()) {
    return false;
  }
  for (size_t i = 0; i < m_dimensions.size(); ++i) {
    if (m_dimensions[i] != other_array->m_dimensions[i]) {
      return false;
    }
  }

  return true;
}

bool ArrayType::operator<=(const Type &other) const {
  if (other.getKind() != TypeKind::kArray) {
    return false;
  }

  const auto *other_array = static_cast<const ArrayType *>(&other);

  if ((*m_underlying_type > *other_array->m_underlying_type)) {
    return false;
  }

  if (m_dimensions.size() != other_array->m_dimensions.size()) {
    return false;
  }

  for (size_t i = 0; i < m_dimensions.size(); ++i) {

    if (other_array->m_dimensions[i] == static_cast<size_t>(-1)) {
      // -1 means the dimension is not specified, so it can be any size
      // e.g case var x:int[2][3] =  j[] /; where j is [5][6][7] and j[] is
      // j[6][7]
      continue;
    }

    if (m_dimensions[i] > other_array->m_dimensions[i]) {
      return false;
    }
  }

  return true;
}

const std::vector<size_t> &ArrayType::getDimensions() const {
  return m_dimensions;
}

std::shared_ptr<Type> ArrayType::getUnderlyingType() const {
  return m_underlying_type;
}

std::string
ArrayType::buildArrayTypeName(std::shared_ptr<Type> underlying_type,
                              const std::vector<size_t> &dimensions) {
  std::stringstream ss;
  ss << "Array: <";
  ss << underlying_type->getName();
  for (size_t i = 0; i < dimensions.size(); ++i) {
    ss << "[";
    ss << dimensions[i];
    ss << "]";
  }
  ss << ">";
  return ss.str();
}

} // namespace types
} // namespace flow_wing