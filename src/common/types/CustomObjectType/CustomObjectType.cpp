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

#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/Type.hpp"
#include <sstream>

namespace flow_wing {
namespace types {

CustomObjectType::CustomObjectType(
    const std::string &custom_type_name,
    const std::map<std::string, std::shared_ptr<Type>> &field_types_map)
    : Type(custom_type_name, TypeKind::kObject),
      m_custom_type_name(custom_type_name),
      m_field_types_map(std::move(field_types_map)) {}

bool CustomObjectType::operator==(const Type &other) const {
  // if (other.isNirast()) {
  //   return true;
  // }

  if (other.getKind() != TypeKind::kObject) {
    return false;
  }

  const auto *other_custom_object =
      static_cast<const CustomObjectType *>(&other);

  if (this == other_custom_object) {
    return true;
  }

  if (m_field_types_map.size() !=
      other_custom_object->m_field_types_map.size()) {
    return false;
  }

  for (const auto &[field_name, field_type] : m_field_types_map) {
    const auto &other_field_type =
        other_custom_object->m_field_types_map.find(field_name);
    if (other_field_type == other_custom_object->m_field_types_map.end() ||
        *field_type != *other_field_type->second) {
      return false;
    }
  }

  return true;
}

const std::map<std::string, std::shared_ptr<Type>> &
CustomObjectType::getFieldTypesMap() const {
  return m_field_types_map;
}

const std::string &CustomObjectType::getCustomTypeName() const {
  return m_custom_type_name;
}

bool CustomObjectType::isObjectExpression() const {
  return m_custom_type_name == "object_expression";
}

bool CustomObjectType::operator<=(const Type &other) const {

  // if (other.isNirast()) {
  //   return true;
  // }

  if (other.getKind() != TypeKind::kObject) {
    return false;
  }

  const auto *other_custom_object =
      static_cast<const CustomObjectType *>(&other);

  if (this == other_custom_object) {
    return true;
  }

  if (m_field_types_map.size() >
      other_custom_object->m_field_types_map.size()) {
    return false;
  }

  for (const auto &[field_name, field_type] : m_field_types_map) {
    const auto &other_field_type =
        other_custom_object->m_field_types_map.find(field_name);
    if (other_field_type == other_custom_object->m_field_types_map.end() ||
        *field_type > *other_field_type->second) {
      return false;
    }
  }
  return true;
}

void CustomObjectType::setFieldTypesMap(
    std::map<std::string, std::shared_ptr<Type>> field_types_map) {
  m_field_types_map = std::move(field_types_map);
  m_name = buildCustomObjectTypeName(m_custom_type_name, m_field_types_map);
}

std::string CustomObjectType::buildCustomObjectTypeName(
    const std::string &custom_type_name,
    const std::map<std::string, std::shared_ptr<Type>> &field_types_map) {
  std::stringstream ss;
  ss << "Object: <" << custom_type_name << " {";
  size_t count = 0, total_fields = field_types_map.size();
  for (const auto &[field_name, field_type] : field_types_map) {
    ss << " " << field_name << ": " << field_type->getName();
    count++;
    if (count < total_fields - 1) {
      ss << ",";
    } else {
      ss << " ";
    }
  }

  ss << "}>";
  return ss.str();
}
} // namespace types
} // namespace flow_wing