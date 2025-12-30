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
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"

namespace flow_wing {
namespace analysis {

// Define all the static variables that were declared in the header
std::shared_ptr<types::Type> Builtins::m_int8_type_instance;
std::shared_ptr<types::Type> Builtins::m_char_type_instance;
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
      std::move(params), std::move(return_types), (size_t)-1, is_variadic,
      true);

  auto function_symbol = std::make_shared<FunctionSymbol>(name, function_type);

  m_all_symbols.push_back(function_symbol);
  m_functions_symbols_map[name].push_back(function_symbol);
}

void Builtins::createInternalFunction(
    const std::string &name, std::vector<std::shared_ptr<types::Type>> params,
    std::vector<std::shared_ptr<types::Type>> returns, bool is_variadic) {

  std::vector<std::shared_ptr<types::ParameterType>> param_types;
  for (const auto &param : params) {
    param_types.push_back(std::make_shared<types::ParameterType>(
        param, types::ValueKind::kByValue, types::TypeConvention::kC));
  }

  std::vector<std::shared_ptr<types::ReturnType>> return_types;
  for (const auto &ret : returns) {
    return_types.push_back(
        std::make_shared<types::ReturnType>(ret, types::TypeConvention::kC));
  }

  auto function_type = std::make_shared<types::FunctionType>(
      std::move(param_types), std::move(return_types), (size_t)-1, is_variadic,
      true);

  auto function_symbol = std::make_shared<FunctionSymbol>(name, function_type);

  m_all_symbols.push_back(function_symbol);
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
                        false);
}

bool Builtins::initialize(binding::BinderContext *context) {

  m_int8_type_instance = createBuiltinType("int8");
  m_char_type_instance = createBuiltinType("char");
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
      {std::make_shared<types::ReturnType>(Builtins::m_nthg_type_instance,
                                           types::TypeConvention::kC)},
      true);

  createBuiltinFunction(
      "input",
      {{std::make_shared<types::ParameterType>(Builtins::m_str_type_instance,
                                               types::ValueKind::kByValue,
                                               types::TypeConvention::kC)}},
      {std::make_shared<types::ReturnType>(Builtins::m_str_type_instance,
                                           types::TypeConvention::kC)},
      false);

  // --- Int32, Int8, Int64 Conversion Overloads ---

  auto int8Fn = std::string(ir_gen::constants::functions::kInt8_fn);
  auto int32Fn = std::string(ir_gen::constants::functions::kInt32_fn);
  auto int64Fn = std::string(ir_gen::constants::functions::kInt64_fn);
  auto deciFn = std::string(ir_gen::constants::functions::kDecimal_fn);
  auto deci32Fn = std::string(ir_gen::constants::functions::kDecimal32_fn);
  auto boolFn = std::string(ir_gen::constants::functions::kBool_fn);
  auto stringFn = std::string(ir_gen::constants::functions::kString_fn);

  for (const auto &param_type : {
           Builtins::m_str_type_instance,
           Builtins::m_int8_type_instance,
           Builtins::m_int32_type_instance,
           Builtins::m_int64_type_instance,
           Builtins::m_char_type_instance,
           Builtins::m_deci32_type_instance,
           Builtins::m_deci_type_instance,
           Builtins::m_bool_type_instance,
       }) {
    createBuiltinFunctionOverloads(int8Fn, param_type,
                                   Builtins::m_int8_type_instance);
    createBuiltinFunctionOverloads(int32Fn, param_type,
                                   Builtins::m_int32_type_instance);
    createBuiltinFunctionOverloads(int64Fn, param_type,
                                   Builtins::m_int64_type_instance);

    createBuiltinFunctionOverloads(deci32Fn, param_type,
                                   Builtins::m_deci32_type_instance);
    createBuiltinFunctionOverloads(deciFn, param_type,
                                   Builtins::m_deci_type_instance);

    createBuiltinFunctionOverloads(boolFn, param_type,
                                   Builtins::m_bool_type_instance);
    createBuiltinFunctionOverloads(stringFn, param_type,
                                   Builtins::m_str_type_instance);
  }

  // -- Char Conversion Overloads --
  auto charFn = std::string(ir_gen::constants::functions::kChar_fn);

  for (const auto &param_type : {
           Builtins::m_str_type_instance,
           Builtins::m_int32_type_instance,
           Builtins::m_int8_type_instance,
           Builtins::m_char_type_instance,
           Builtins::m_int64_type_instance,
       }) {

    createBuiltinFunctionOverloads(charFn, param_type,
                                   Builtins::m_char_type_instance);
  }

  // Internal Functions
  initializeInternalFunctions();

  for (const auto &symbol : m_all_symbols) {
    context->getSymbolTable()->define(symbol);
  }

  return true;
}

void Builtins::initializeInternalFunctions() {

  createInternalFunction(std::string(ir_gen::constants::functions::kPrintf_fn),
                         {Builtins::m_str_type_instance},
                         {Builtins::m_nthg_type_instance}, true);

  createInternalFunction(
      std::string(ir_gen::constants::functions::kConcat_strings_fn),
      {
          Builtins::m_str_type_instance,
          Builtins::m_str_type_instance,
      },
      {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kString_length_fn),
      {
          Builtins::m_str_type_instance,
      },
      {Builtins::m_int32_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kItos_fn),
                         {Builtins::m_int32_type_instance},
                         {Builtins::m_str_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kI8tos_fn),
                         {Builtins::m_int8_type_instance},
                         {Builtins::m_str_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kDtos_fn),
                         {Builtins::m_deci_type_instance},
                         {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(
          ir_gen::constants::functions::kGet_malloc_ptr_of_string_constant_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(
          ir_gen::constants::functions::kGet_malloc_ptr_of_int_constant_fn),
      {Builtins::m_int32_type_instance}, {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kCompare_strings_fn),
      {Builtins::m_str_type_instance, Builtins::m_str_type_instance},
      {Builtins::m_int32_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kLess_than_strings_fn),
      {Builtins::m_str_type_instance, Builtins::m_str_type_instance},
      {Builtins::m_bool_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kLess_than_or_equal_strings_fn),
      {Builtins::m_str_type_instance, Builtins::m_str_type_instance},
      {Builtins::m_bool_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kGreater_than_strings_fn),
      {Builtins::m_str_type_instance, Builtins::m_str_type_instance},
      {Builtins::m_bool_type_instance});

  createInternalFunction(
      std::string(
          ir_gen::constants::functions::kGreater_than_or_equal_strings_fn),
      {Builtins::m_str_type_instance, Builtins::m_str_type_instance},
      {Builtins::m_bool_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kEqual_strings_fn),
      {Builtins::m_str_type_instance, Builtins::m_str_type_instance},
      {Builtins::m_bool_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kGet_input_fn), {},
      {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kString_to_int_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_int32_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kString_to_char_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_char_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kString_to_long_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_int64_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kString_to_double_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_deci_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kRaise_exception_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_nthg_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kMalloc_fn),
                         {Builtins::m_int64_type_instance},
                         {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kGC_malloc_fn),
      {Builtins::m_int64_type_instance}, {Builtins::m_str_type_instance});

  createInternalFunction(
      std::string(ir_gen::constants::functions::kString_to_float_fn),
      {Builtins::m_str_type_instance}, {Builtins::m_deci32_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kCtos_fn),
                         {Builtins::m_char_type_instance},
                         {Builtins::m_str_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kLltos_fn),
                         {Builtins::m_int64_type_instance},
                         {Builtins::m_str_type_instance});

  createInternalFunction(std::string(ir_gen::constants::functions::kFtos_fn),
                         {Builtins::m_deci32_type_instance},
                         {Builtins::m_str_type_instance});
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