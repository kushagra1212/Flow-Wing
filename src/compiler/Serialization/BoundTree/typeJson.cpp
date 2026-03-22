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

#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"
#include <map>
#include <string>

namespace flow_wing::compiler::serializer {

void BoundTreeJson::collectInstanceFieldsFlat(
    const types::ClassType *class_type,
    std::map<std::string, std::string> &name_to_type_id) {
  if (class_type->getBaseClass()) {
    collectInstanceFieldsFlat(class_type->getBaseClass().get(), name_to_type_id);
  }
  for (const auto &[name, sym] : class_type->getFieldMembers()) {
    if (sym->getKind() == analysis::SymbolKind::kVariable) {
      name_to_type_id[name] = getTypeId(sym->getType().get());
    }
  }
}

void BoundTreeJson::collectMethodsFlat(
    const types::ClassType *class_type,
    std::map<std::string, std::string> &name_to_type_id) {
  if (class_type->getBaseClass()) {
    collectMethodsFlat(class_type->getBaseClass().get(), name_to_type_id);
  }
  class_type->forEachFunctionMember(
      [&](const std::shared_ptr<analysis::Symbol> &sym) {
        name_to_type_id[sym->getName()] = getTypeId(sym->getType().get());
      });
}

std::string
BoundTreeJson::getTypeId(const types::ParameterType *parameter_type) {
  PARSER_DEBUG_LOG("Visiting Parameter Type", "BOUND TREE");
  nlohmann::json parameter_type_json;

  parameter_type_json["kind"] = "ParameterType";
  parameter_type_json["base_type_id"] = getTypeId(parameter_type->type.get());
  parameter_type_json["value_kind"] =
      types::toString(parameter_type->value_kind);
  parameter_type_json["type_convention"] =
      types::toString(parameter_type->type_convention);
  parameter_type_json["constness"] = types::toString(parameter_type->constness);

  const auto &parameter_type_id = getShortId(parameter_type);
  m_types_json[parameter_type_id] = parameter_type_json;

  return parameter_type_id;
}
std::string BoundTreeJson::getTypeId(const types::ReturnType *return_type) {
  PARSER_DEBUG_LOG("Visiting Return Type", "BOUND TREE");
  nlohmann::json return_type_json;
  return_type_json["kind"] = "ReturnType";
  return_type_json["base_type_id"] = getTypeId(return_type->type.get());
  return_type_json["type_convention"] =
      types::toString(return_type->type_convention);

  const auto &return_type_id = getShortId(return_type);
  m_types_json[return_type_id] = return_type_json;

  return return_type_id;
}

std::string BoundTreeJson::getTypeId(const types::Type *type) {
  switch (type->getKind()) {
  case types::TypeKind::kFunction:
    return getTypeId(static_cast<const types::FunctionType *>(type));
  case types::TypeKind::kArray:
    return getTypeId(static_cast<const types::ArrayType *>(type));
  case types::TypeKind::kClass:
    return getTypeId(static_cast<const types::ClassType *>(type));
  default:
    break;
  }
  PARSER_DEBUG_LOG("Visiting Type", "BOUND TREE");
  nlohmann::json type_json;
  type_json["kind"] = types::Type::toString(type->getKind());
  type_json["name"] = type->getName();

  const auto &type_id = getShortId(type);

  m_types_json[type_id] = type_json;

  return type_id;
}

std::string BoundTreeJson::getTypeId(const types::ClassType *class_type) {
  PARSER_DEBUG_LOG("Visiting Class Type", "BOUND TREE");
  std::string type_id = getShortId(class_type);
  // Methods/parameters may reference this class type (e.g. implicit self); register
  // early so recursive getTypeId(class_type) returns without re-entering.
  if (m_types_json.contains(type_id)) {
    return type_id;
  }
  m_types_json[type_id] = nlohmann::json{{"kind", types::Type::toString(class_type->getKind())},
                                          {"name", class_type->getName()}};

  nlohmann::json type_json;
  type_json["kind"] = types::Type::toString(class_type->getKind());
  type_json["name"] = class_type->getName();
  if (class_type->getBaseClass()) {
    type_json["base_class_type_id"] =
        getTypeId(class_type->getBaseClass().get());
  }
  std::map<std::string, std::string> fields_flat;
  collectInstanceFieldsFlat(class_type, fields_flat);
  for (const auto &[name, tid] : fields_flat) {
    nlohmann::json mf;
    mf["name"] = name;
    mf["type_id"] = tid;
    type_json["member_fields"].push_back(mf);
  }
  std::map<std::string, std::string> methods_flat;
  collectMethodsFlat(class_type, methods_flat);
  for (const auto &[name, tid] : methods_flat) {
    nlohmann::json mo;
    mo["name"] = name;
    mo["type_id"] = tid;
    type_json["methods"].push_back(mo);
  }

  m_types_json[type_id] = std::move(type_json);

  return type_id;
}

std::string BoundTreeJson::getTypeId(const types::ArrayType *array_type) {
  PARSER_DEBUG_LOG("Visiting Array Type", "BOUND TREE");
  nlohmann::json array_type_json;
  array_type_json["kind"] = types::Type::toString(array_type->getKind());
  array_type_json["name"] = array_type->getName();
  array_type_json["underlying_type_id"] =
      getTypeId(array_type->getUnderlyingType().get());
  for (const auto &dimension : array_type->getDimensions()) {
    array_type_json["dimensions"].push_back(dimension);
  }
  const auto &array_type_id = getShortId(array_type);
  m_types_json[array_type_id] = array_type_json;

  return array_type_id;
}

std::string BoundTreeJson::getTypeId(const types::FunctionType *function_type) {
  PARSER_DEBUG_LOG("Visiting Function Type", "BOUND TREE");
  nlohmann::json function_type_json;
  function_type_json["kind"] = types::Type::toString(function_type->getKind());
  function_type_json["name"] = function_type->getName();

  for (const auto &parameter : function_type->getParameterTypes()) {
    function_type_json["parameter_type_ids"].push_back(
        getTypeId(parameter.get()));
  }

  for (const auto &return_type : function_type->getReturnTypes()) {
    function_type_json["return_type_ids"].push_back(
        getTypeId(return_type.get()));
  }

  const auto &type_id = getShortId(function_type);
  m_types_json[type_id] = function_type_json;

  return type_id;
}
} // namespace flow_wing::compiler::serializer