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

#include "src/common/types/Type.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"

namespace flow_wing {
namespace types {

Type::Type(std::string name, TypeKind kind)
    : m_name(std::move(name)), m_kind(kind) {}

bool Type::operator==(const Type &other) const {

  for (auto const &type_kind : {TypeKind::kPrimitive, TypeKind::kClass}) {
    if ((this->getKind() == type_kind && other.isDynamic()) ||
        (other.getKind() == type_kind && this->isDynamic())) {
      return true;
    }
  }

  return this->getName() == other.getName() &&
         this->getKind() == other.getKind();
}
bool Type::operator!=(const Type &other) const { return !(*this == other); }

bool Type::operator<=(const Type &other) const {

  if (this->isNirast() && other.getKind() == TypeKind::kObject) {
    return true;
  }

  // If types are equal, they are compatible
  if (*this == other) {
    return true;
  }

  // Only primitives have implicit conversion rules
  if (this->getKind() != TypeKind::kPrimitive ||
      other.getKind() != TypeKind::kPrimitive) {
    return false;
  }

  const std::string &this_name = this->getName();
  const std::string &other_name = other.getName();

  // Integer promotion: int8 <= int (int32) <= int64
  if (this_name == "int8") {
    return other_name == "int" || other_name == "int64";
  }
  if (this_name == "int") {
    return other_name == "int64";
  }

  // Decimal promotion: deci32 <= deci
  if (this_name == "deci32") {
    return other_name == "deci";
  }

  // String promotion: char <= str
  if (this_name == "char") {
    return other_name == "str";
  }

  return false;
}
bool Type::operator>(const Type &other) const { return !(*this <= other); }

bool Type::isNthg() const {
  return this == analysis::Builtins::m_nthg_type_instance.get();
}

bool Type::isDynamic() const {
  return this == analysis::Builtins::m_dynamic_type_instance.get();
}

bool Type::isNirast() const {
  return this == analysis::Builtins::m_nirast_type_instance.get();
}

bool Type::isPrimitive() const { return m_kind == TypeKind::kPrimitive; }

std::string Type::toString(TypeKind kind) {
  switch (kind) {
  case TypeKind::kPrimitive:
    return "Primitive";
  case TypeKind::kFunction:
    return "Function";
  case TypeKind::kObject:
    return "Object";
  case TypeKind::kModule:
    return "Module";
  case TypeKind::kArray:
    return "Array";
  case TypeKind::kClass:
    return "Class";
  case TypeKind::kError:
    return "Error";
  }
  return "Unknown";
}
} // namespace types
} // namespace flow_wing