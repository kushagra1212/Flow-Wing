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

#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

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
  PARSER_DEBUG_LOG("Visiting Type", "BOUND TREE");
  nlohmann::json type_json;
  type_json["kind"] = types::Type::toString(type->getKind());
  type_json["name"] = type->getName();

  const auto &type_id = getShortId(type);

  m_types_json[type_id] = type_json;

  return type_id;
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