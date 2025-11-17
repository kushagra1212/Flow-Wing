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



#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"

namespace flow_wing {
namespace analysis {

// Define all the static variables that were declared in the header
std::shared_ptr<types::Type> Builtins::m_int8_type_instance;
std::shared_ptr<types::Type> Builtins::m_int32_type_instance;
std::shared_ptr<types::Type> Builtins::m_int64_type_instance;
std::shared_ptr<types::Type> Builtins::m_deci_type_instance;
std::shared_ptr<types::Type> Builtins::m_deci32_type_instance;
std::shared_ptr<types::Type> Builtins::m_str_type_instance;
std::shared_ptr<types::Type> Builtins::m_bool_type_instance;
std::shared_ptr<types::Type> Builtins::m_nirast_type_instance;
std::shared_ptr<types::Type> Builtins::m_nthg_type_instance;
std::shared_ptr<types::Type> Builtins::m_dynamic_type_instance;

std::vector<std::shared_ptr<Symbol>> Builtins::m_all_symbols;
std::unordered_map<std::string, std::vector<std::shared_ptr<Symbol>>>
    Builtins::m_functions_symbols_map;
std::unordered_map<std::string, std::shared_ptr<Symbol>>
    Builtins::m_types_symbols_map;

} // namespace analysis
} // namespace flow_wing

namespace flow_wing {
namespace analysis {

std::shared_ptr<types::Type>
Builtins::createBuiltinType(const std::string &name) {
  auto type_instance =
      std::make_shared<types::Type>(name, types::TypeKind::kPrimitive);

  auto type_symbol =
      std::make_shared<Symbol>(name, SymbolKind::kType, type_instance);

  m_all_symbols.push_back(type_symbol);
  m_types_symbols_map[name] = type_symbol;

  return type_instance;
}

void Builtins::createBuiltinFunction(
    const std::string &name,
    std::vector<std::shared_ptr<types::ParameterType>> params,
    std::vector<std::shared_ptr<types::ReturnType>> return_types,
    bool is_variadic) {

  auto function_type = std::make_shared<types::FunctionType>(
      std::move(params), std::move(return_types), is_variadic);

  auto function_symbol =
      std::make_shared<Symbol>(name, SymbolKind::kFunction, function_type);

  m_all_symbols.push_back(function_symbol);
  m_functions_symbols_map[name].push_back(function_symbol);
}

void Builtins::createBuiltinFunctionOverloads(
    const std::string &name, std::shared_ptr<types::Type> param_type,
    std::shared_ptr<types::Type> return_type) {

  auto params = std::vector<std::shared_ptr<types::ParameterType>>();

  if (param_type) {
    params.push_back(std::make_shared<types::ParameterType>(param_type));
  }

  createBuiltinFunction(name, std::move(params),
                        {std::make_shared<types::ReturnType>(return_type)},
                        true);
}

bool Builtins::initialize() {

  m_int8_type_instance = createBuiltinType("int8");
  m_int32_type_instance = createBuiltinType("int");
  m_int64_type_instance = createBuiltinType("int64");
  m_deci_type_instance = createBuiltinType("deci");
  m_deci32_type_instance = createBuiltinType("deci32");
  m_str_type_instance = createBuiltinType("str");
  m_bool_type_instance = createBuiltinType("bool");
  m_nthg_type_instance = createBuiltinType("nthg");
  m_dynamic_type_instance = createBuiltinType("dynamic");
  m_nirast_type_instance = createBuiltinType("Nir");

  createBuiltinFunction(
      "print", {},
      {std::make_shared<types::ReturnType>(Builtins::m_nthg_type_instance)},
      true);

  createBuiltinFunction(
      "input",
      {{std::make_shared<types::ParameterType>(Builtins::m_str_type_instance)}},
      {std::make_shared<types::ReturnType>(Builtins::m_str_type_instance)},
      false);

  // --- Int32 Conversion Overloads ---
  createBuiltinFunctionOverloads("Int32", Builtins::m_str_type_instance,
                                 Builtins::m_int32_type_instance);
  createBuiltinFunctionOverloads("Int32", Builtins::m_int8_type_instance,
                                 Builtins::m_int32_type_instance);
  createBuiltinFunctionOverloads("Int32", Builtins::m_int64_type_instance,
                                 Builtins::m_int32_type_instance);
  createBuiltinFunctionOverloads("Int32", Builtins::m_deci_type_instance,
                                 Builtins::m_int32_type_instance);
  createBuiltinFunctionOverloads("Int32", Builtins::m_deci32_type_instance,
                                 Builtins::m_int32_type_instance);
  createBuiltinFunctionOverloads("Int32", Builtins::m_bool_type_instance,
                                 Builtins::m_int32_type_instance);
  createBuiltinFunctionOverloads("Int32", Builtins::m_dynamic_type_instance,
                                 Builtins::m_int32_type_instance);

  // -- Int8 Conversion Overloads --
  createBuiltinFunctionOverloads("Int8", Builtins::m_str_type_instance,
                                 Builtins::m_int8_type_instance);
  createBuiltinFunctionOverloads("Int8", Builtins::m_int32_type_instance,
                                 Builtins::m_int8_type_instance);
  createBuiltinFunctionOverloads("Int8", Builtins::m_int64_type_instance,
                                 Builtins::m_int8_type_instance);
  createBuiltinFunctionOverloads("Int8", Builtins::m_deci_type_instance,
                                 Builtins::m_int8_type_instance);
  createBuiltinFunctionOverloads("Int8", Builtins::m_deci32_type_instance,
                                 Builtins::m_int8_type_instance);
  createBuiltinFunctionOverloads("Int8", Builtins::m_bool_type_instance,
                                 Builtins::m_int8_type_instance);
  createBuiltinFunctionOverloads("Int8", Builtins::m_dynamic_type_instance,
                                 Builtins::m_int8_type_instance);

  // -- Decimal Conversion Overloads --
  createBuiltinFunctionOverloads("Decimal", Builtins::m_str_type_instance,
                                 Builtins::m_deci_type_instance);
  createBuiltinFunctionOverloads("Decimal", Builtins::m_int32_type_instance,
                                 Builtins::m_deci_type_instance);
  createBuiltinFunctionOverloads("Decimal", Builtins::m_int8_type_instance,
                                 Builtins::m_deci_type_instance);
  createBuiltinFunctionOverloads("Decimal", Builtins::m_int64_type_instance,
                                 Builtins::m_deci_type_instance);
  createBuiltinFunctionOverloads("Decimal", Builtins::m_deci32_type_instance,
                                 Builtins::m_deci_type_instance);
  createBuiltinFunctionOverloads("Decimal", Builtins::m_bool_type_instance,
                                 Builtins::m_deci_type_instance);
  createBuiltinFunctionOverloads("Decimal", Builtins::m_dynamic_type_instance,
                                 Builtins::m_deci_type_instance);

  // -- Deci32 Conversion Overloads --
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_str_type_instance,
                                 Builtins::m_deci32_type_instance);
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_int32_type_instance,
                                 Builtins::m_deci32_type_instance);
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_int8_type_instance,
                                 Builtins::m_deci32_type_instance);
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_int64_type_instance,
                                 Builtins::m_deci32_type_instance);
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_bool_type_instance,
                                 Builtins::m_deci32_type_instance);
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_dynamic_type_instance,
                                 Builtins::m_deci32_type_instance);
  createBuiltinFunctionOverloads("Decimal32", Builtins::m_deci_type_instance,
                                 Builtins::m_deci32_type_instance);

  // -- Bool Conversion Overloads --
  createBuiltinFunctionOverloads("Bool", Builtins::m_str_type_instance,
                                 Builtins::m_bool_type_instance);
  createBuiltinFunctionOverloads("Bool", Builtins::m_int32_type_instance,
                                 Builtins::m_bool_type_instance);
  createBuiltinFunctionOverloads("Bool", Builtins::m_int8_type_instance,
                                 Builtins::m_bool_type_instance);
  createBuiltinFunctionOverloads("Bool", Builtins::m_int64_type_instance,
                                 Builtins::m_bool_type_instance);
  createBuiltinFunctionOverloads("Bool", Builtins::m_deci32_type_instance,
                                 Builtins::m_bool_type_instance);
  createBuiltinFunctionOverloads("Bool", Builtins::m_dynamic_type_instance,
                                 Builtins::m_bool_type_instance);
  createBuiltinFunctionOverloads("Bool", Builtins::m_deci_type_instance,
                                 Builtins::m_bool_type_instance);

  // -- String Conversion Overloads --
  createBuiltinFunctionOverloads("String", Builtins::m_int32_type_instance,
                                 Builtins::m_str_type_instance);
  createBuiltinFunctionOverloads("String", Builtins::m_int8_type_instance,
                                 Builtins::m_str_type_instance);
  createBuiltinFunctionOverloads("String", Builtins::m_int64_type_instance,
                                 Builtins::m_str_type_instance);
  createBuiltinFunctionOverloads("String", Builtins::m_deci32_type_instance,
                                 Builtins::m_str_type_instance);
  createBuiltinFunctionOverloads("String", Builtins::m_bool_type_instance,
                                 Builtins::m_str_type_instance);
  createBuiltinFunctionOverloads("String", Builtins::m_dynamic_type_instance,
                                 Builtins::m_str_type_instance);
  createBuiltinFunctionOverloads("String", Builtins::m_deci_type_instance,
                                 Builtins::m_str_type_instance);

  return true;
}

bool Builtins::isBuiltInFunction(const std::string &name) {
  return m_functions_symbols_map.find(name) != m_functions_symbols_map.end();
}

bool Builtins::isBuiltInType(const std::string &name) {
  return m_types_symbols_map.find(name) != m_types_symbols_map.end();
}

const std::vector<std::shared_ptr<Symbol>> &Builtins::getAll() {
  return m_all_symbols;
}

} // namespace analysis
} // namespace flow_wing