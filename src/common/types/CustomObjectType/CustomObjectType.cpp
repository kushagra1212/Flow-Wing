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


#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/common/types/Type.hpp"
#include <sstream>

namespace flow_wing {
namespace types {

CustomObjectType::CustomObjectType(
    const std::string &custom_type_name,
    std::map<std::string, std::shared_ptr<Type>> fields)
    : Type(buildCustomObjectTypeName(custom_type_name, fields),
           TypeKind::kObject),
      m_custom_type_name(custom_type_name), m_fields(std::move(fields)) {}

bool CustomObjectType::operator==(const Type &other) const {
  if (other.getKind() != TypeKind::kObject) {
    return false;
  }

  const auto *other_custom_object =
      static_cast<const CustomObjectType *>(&other);

  if (m_fields.size() != other_custom_object->m_fields.size()) {
    return false;
  }

  for (const auto &[field_name, field_type] : m_fields) {

    auto it = other_custom_object->m_fields.find(field_name);
    if (it == other_custom_object->m_fields.end()) {
      return false; // Field name not found
    }

    if (*field_type != *it->second) {
      return false;
    }
  }

  return true;
}

bool CustomObjectType::operator<=(const Type &other) const {
  if (other.getKind() != TypeKind::kObject) {
    return false;
  }

  const auto *other_custom_object =
      static_cast<const CustomObjectType *>(&other);

  if (m_fields.size() > other_custom_object->m_fields.size()) {
    return false;
  }

  for (const auto &[field_name, field_type] : m_fields) {
    auto it = other_custom_object->m_fields.find(field_name);
    if (it == other_custom_object->m_fields.end()) {
      return false;
    }

    if (*field_type > *it->second) {
      return false;
    }
  }

  return true;
}

std::shared_ptr<Type>
CustomObjectType::getFieldType(const std::string &name) const {
  auto it = m_fields.find(name);
  if (it == m_fields.end()) {
    return nullptr;
  }
  return it->second;
}

std::string CustomObjectType::buildCustomObjectTypeName(
    const std::string &custom_type_name,
    const std::map<std::string, std::shared_ptr<Type>> &fields) {
  std::stringstream ss;
  ss << "Object: <" << custom_type_name << " {";
  for (const auto &[field_name, field_type] : fields) {
    ss << field_name << ": " << field_type->getName() << ", ";
  }
  ss << "}>";
  return ss.str();
}
} // namespace types
} // namespace flow_wing