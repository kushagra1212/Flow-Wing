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

#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/compiler/Serialization/BoundTree/BoundTreeJson.hpp"

namespace flow_wing::compiler::serializer {

void BoundTreeJson::attachDeclarationSite(nlohmann::json &j,
                                          const analysis::Symbol *symbol) {
  if (!symbol || !symbol->hasDeclarationSite())
    return;
  if (const auto &p = symbol->getDeclarationSourcePath())
    j["declaration_source"] = *p;
  const auto &locOpt = symbol->getDeclarationLocation();
  if (locOpt.has_value())
    j["declaration_range"] = toJsonRange(*locOpt);
}

std::string BoundTreeJson::getSymbolId(const analysis::Symbol *symbol) {

  switch (symbol->getKind()) {
  case analysis::SymbolKind::kVariable:
    return getSymbolId(static_cast<const analysis::VariableSymbol *>(symbol));
  case analysis::SymbolKind::kFunction:
    return getSymbolId(static_cast<const analysis::FunctionSymbol *>(symbol));
  case analysis::SymbolKind::kParameter:
    return getSymbolId(static_cast<const analysis::ParameterSymbol *>(symbol));
  case analysis::SymbolKind::kModule:
    return getSymbolId(static_cast<const analysis::ModuleSymbol *>(symbol));
  default: {
    nlohmann::json object_symbol_json;
    object_symbol_json["kind"] = analysis::Symbol::toString(symbol->getKind());
    object_symbol_json["name"] = symbol->getName();
    object_symbol_json["type_id"] = getTypeId(symbol->getType().get());
    attachDeclarationSite(object_symbol_json, symbol);
    const auto &object_symbol_id = getShortId(symbol);
    m_symbols_json[object_symbol_id] = object_symbol_json;
    return object_symbol_id;
  }
  }
  return "Unknown Symbol Kind";
}

std::string BoundTreeJson::getSymbolId(
    const analysis::ModuleSymbol *module_symbol) {
  PARSER_DEBUG_LOG("Visiting Module Symbol", "BOUND TREE");
  nlohmann::json module_symbol_json;
  module_symbol_json["kind"] =
      analysis::Symbol::toString(module_symbol->getKind());
  module_symbol_json["name"] = module_symbol->getName();
  module_symbol_json["type_id"] = getTypeId(module_symbol->getType().get());
  const auto &symbol_id = getShortId(module_symbol);
  attachDeclarationSite(module_symbol_json, module_symbol);
  m_symbols_json[symbol_id] = module_symbol_json;
  return symbol_id;
}

std::string
BoundTreeJson::getSymbolId(const analysis::FunctionSymbol *function_symbol) {
  PARSER_DEBUG_LOG("Visiting Function Symbol", "BOUND TREE");
  nlohmann::json function_symbol_json;
  function_symbol_json["kind"] =
      analysis::Symbol::toString(function_symbol->getKind());
  function_symbol_json["name"] = function_symbol->getName();
  function_symbol_json["type_id"] =
      getTypeId(static_cast<const types::FunctionType *>(
          function_symbol->getType().get()));
  const auto &symbol_id = getShortId(function_symbol);
  function_symbol_json["is_declaration"] =
      function_symbol->getBody() == nullptr;
  function_symbol_json["hide_trailing_params_for_display"] =
      function_symbol->getHideTrailingParamsForDisplay();

  for (const auto &parameter : function_symbol->getParameters()) {
    function_symbol_json["parameters"].push_back(getSymbolId(parameter.get()));
  }

  attachDeclarationSite(function_symbol_json, function_symbol);

  m_symbols_json[symbol_id] = function_symbol_json;

  return symbol_id;
};

std::string
BoundTreeJson::getSymbolId(const analysis::ParameterSymbol *parameter_symbol) {
  PARSER_DEBUG_LOG("Visiting Parameter Symbol", "BOUND TREE");
  nlohmann::json parameter_symbol_json;
  parameter_symbol_json["kind"] =
      analysis::Symbol::toString(parameter_symbol->getKind());
  parameter_symbol_json["name"] = parameter_symbol->getName();
  parameter_symbol_json["type_id"] =
      getTypeId(parameter_symbol->getType().get());

  parameter_symbol_json["has_default_value"] =
      parameter_symbol->getDefaultValueExpression() != nullptr;

  const auto &parameter_symbol_id = getShortId(parameter_symbol);
  attachDeclarationSite(parameter_symbol_json, parameter_symbol);

  m_symbols_json[parameter_symbol_id] = parameter_symbol_json;

  return parameter_symbol_id;
}

std::string
BoundTreeJson::getSymbolId(const analysis::VariableSymbol *variable_symbol) {

  PARSER_DEBUG_LOG("Visiting Variable Symbol", "BOUND TREE");
  nlohmann::json variable_symbol_json;
  variable_symbol_json["kind"] =
      analysis::Symbol::toString(variable_symbol->getKind());
  variable_symbol_json["name"] = variable_symbol->getName();
  variable_symbol_json["type_id"] = getTypeId(variable_symbol->getType().get());
  variable_symbol_json["isConst"] = variable_symbol->isConst();

  const auto &variable_symbol_id = getShortId(variable_symbol);
  attachDeclarationSite(variable_symbol_json, variable_symbol);

  m_symbols_json[variable_symbol_id] = variable_symbol_json;

  return variable_symbol_id;
}

} // namespace flow_wing::compiler::serializer