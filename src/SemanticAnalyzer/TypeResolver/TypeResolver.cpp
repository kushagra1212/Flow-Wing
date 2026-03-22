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

#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/FunctionReturnTypeExpressionSyntax/FunctionReturnTypeExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/IntegerLiteralExpressionSyntax/IntegerLiteralExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ArrayTypeExpressionSyntax/ArrayTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/FunctionTypeExpressionSyntax/FunctionTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ModuleAccessTypeExpressionSyntax/ModuleAccessTypeExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include "src/syntax/statements/ParameterExpressionSyntax/ParameterExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <any>
#include <cassert>
#include <cstdint>
#include <variant>

namespace flow_wing {
namespace analysis {

TypeResolver::TypeResolver(binding::BinderContext *ctx) : m_ctx(ctx) {}

types::ValueKind TypeResolver::getValueKind(const bool has_inout_keyword) {
  return has_inout_keyword ? types::ValueKind::kByReference
                           : types::ValueKind::kByValue;
}

types::Constness TypeResolver::getConstness(const bool has_const_keyword) {
  return has_const_keyword ? types::Constness::kConst
                           : types::Constness::kMutable;
}

types::TypeConvention
TypeResolver::getTypeConvention(const bool has_as_keyword) {
  return has_as_keyword ? types::TypeConvention::kC
                        : types::TypeConvention::kFlowWing;
}

std::pair<std::shared_ptr<types::Type>,
          std::unique_ptr<binding::BoundErrorExpression>>
TypeResolver::resolveType(const syntax::ExpressionSyntax *syntax) {

  if (syntax == nullptr) {
    return {Builtins::m_dynamic_type_instance, nullptr};
  }

  switch (syntax->getKind()) {
  case syntax::NodeKind::kInt8TypeExpression:
    return {Builtins::m_int8_type_instance, nullptr};
  case syntax::NodeKind::kCharTypeExpression:
    return {Builtins::m_char_type_instance, nullptr};
  case syntax::NodeKind::kInt32TypeExpression:
    return {Builtins::m_int32_type_instance, nullptr};
  case syntax::NodeKind::kInt64TypeExpression:
    return {Builtins::m_int64_type_instance, nullptr};
  case syntax::NodeKind::kDeciTypeExpression:
    return {Builtins::m_deci_type_instance, nullptr};
  case syntax::NodeKind::kDeci32TypeExpression:
    return {Builtins::m_deci32_type_instance, nullptr};
  case syntax::NodeKind::kStrTypeExpression:
    return {Builtins::m_str_type_instance, nullptr};
  case syntax::NodeKind::kBoolTypeExpression:
    return {Builtins::m_bool_type_instance, nullptr};
  case syntax::NodeKind::kNthgTypeExpression:
    return {Builtins::m_nthg_type_instance, nullptr};
  case syntax::NodeKind::kObjectTypeExpression:
    return resolveObjectType(
        static_cast<const syntax::ObjectTypeExpressionSyntax *>(syntax));
  case syntax::NodeKind::kArrayTypeExpression:
    return resolveArrayType(
        static_cast<const syntax::ArrayTypeExpressionSyntax *>(syntax));
  case syntax::NodeKind::kFunctionTypeExpression:
    return resolveFunctionType(
        static_cast<const syntax::FunctionTypeExpressionSyntax *>(syntax));
  case syntax::NodeKind::kModuleAccessTypeExpression:
    return resolveModuleAccessType(
        static_cast<const syntax::ModuleAccessTypeExpressionSyntax *>(syntax));
  default:
    assert(false && "TypeResolver::resolveType: unknown type kind");
    return {nullptr, nullptr};
  }
}

std::pair<std::shared_ptr<types::Type>,
          std::unique_ptr<binding::BoundErrorExpression>>
TypeResolver::resolveModuleAccessType(
    const syntax::ModuleAccessTypeExpressionSyntax *syntax) {

  assert(syntax != nullptr &&
         "TypeResolver::resolveModuleAccessType: syntax is null");

  assert(syntax->getModuleIdentifier() != nullptr &&
         "TypeResolver::resolveModuleAccessType: module identifier is null");

  auto qualifier_name = syntax->getModuleIdentifier()->getValue();

  auto [base_type, error_expression] =
      resolveType(syntax->getTypeExpression().get());

  if (base_type == nullptr) {
    return {nullptr, std::move(error_expression)};
  }

  return {base_type, nullptr};
}

std::unique_ptr<binding::BoundErrorExpression>
TypeResolver::populateDimensionValue(
    const syntax::DimensionClauseExpressionSyntax *syntax, int64_t &value) {

  assert(syntax != nullptr &&
         "TypeResolver::resolveDimensionClause: syntax is null");

  assert(syntax->getSizeLiteral() != nullptr &&
         "TypeResolver::resolveDimensionClause: size literal is null");

  if (syntax->getSizeLiteral()->getKind() !=
      syntax::NodeKind::kNumberLiteralExpression) {

    return std::make_unique<binding::BoundErrorExpression>(
        syntax->getSizeLiteral()->getSourceLocation(),
        flow_wing::diagnostic::DiagnosticCode::kUnexpectedExpression,
        diagnostic::DiagnosticArgs{
            syntax::toString(syntax->getSizeLiteral()->getKind()),
            syntax::toString(syntax::NodeKind::kNumberLiteralExpression)});
  }

  auto number_literal =
      static_cast<const syntax::IntegerLiteralExpressionSyntax *>(
          syntax->getSizeLiteral().get());

  auto int_value = number_literal->getValue();

  if (int_value < 0) {

    return std::make_unique<binding::BoundErrorExpression>(
        syntax->getSizeLiteral()->getSourceLocation(),
        flow_wing::diagnostic::DiagnosticCode::
            kExpectedNonNegativeIntegerForArrayDimension,
        diagnostic::DiagnosticArgs{std::to_string(int_value)});
  }

  value = int_value;
  return nullptr;
}

std::pair<std::shared_ptr<types::Type>,
          std::unique_ptr<binding::BoundErrorExpression>>
TypeResolver::resolveArrayType(
    const syntax::ArrayTypeExpressionSyntax *syntax) {

  assert(syntax != nullptr && "TypeResolver::resolveArrayType: syntax is null");

  // Note: syntax->getUnderlyingType() can be nullptr for dynamic array types
  // like [3][2], which resolves to dynamic base type via resolveType(nullptr)

  assert(!syntax->getDimensions().empty() &&
         "TypeResolver::resolveArrayType: dimensions are empty");

  std::vector<size_t> dimensions;
  for (const auto &dimension : syntax->getDimensions()) {

    int64_t value;
    auto error_expression = populateDimensionValue(dimension.get(), value);
    if (error_expression != nullptr) {
      return {nullptr, std::move(error_expression)};
    }
    dimensions.push_back(static_cast<size_t>(value));
  }

  auto [base_type, error_expression] =
      resolveType(syntax->getUnderlyingType().get());

  if (error_expression != nullptr) {
    return {nullptr, std::move(error_expression)};
  }

  BINDER_DEBUG_LOG("Array Base Type Name: ", base_type->getName());

  return {std::make_shared<types::ArrayType>(base_type, dimensions), nullptr};
}

std::pair<std::shared_ptr<types::Type>,
          std::unique_ptr<binding::BoundErrorExpression>>
TypeResolver::resolveObjectType(
    const syntax::ObjectTypeExpressionSyntax *syntax) {

  assert(syntax != nullptr &&
         "TypeResolver::resolveObjectType: syntax is null");

  auto custom_type_symbol = m_ctx->getSymbolTable()->lookup(
      syntax->getObjectIdentifier()->getValue());

  if (custom_type_symbol == nullptr) {
    return {nullptr,
            std::make_unique<binding::BoundErrorExpression>(
                syntax->getObjectIdentifier()->getSourceLocation(),
                flow_wing::diagnostic::DiagnosticCode::kCustomTypeNotFound,
                diagnostic::DiagnosticArgs{
                    syntax->getObjectIdentifier()->getValue()})};
  }

  if (custom_type_symbol->getKind() == analysis::SymbolKind::kClass) {
    auto class_type = std::dynamic_pointer_cast<types::ClassType>(
        custom_type_symbol->getType());
    assert(class_type && "Class symbol must carry ClassType");
    return {class_type, nullptr};
  }

  auto custom_type_type = std::dynamic_pointer_cast<types::CustomObjectType>(
      custom_type_symbol->getType());

  assert(custom_type_type && "Custom type type is null");

  return {custom_type_type, nullptr};
}

std::shared_ptr<types::ParameterType> TypeResolver::resolveParameterExpression(
    const syntax::ParameterExpressionSyntax *syntax) {
  const bool has_inout_keyword = syntax->hasInoutKeyword();
  const bool has_const_keyword = syntax->hasConstKeyword();
  const bool has_as_keyword = syntax->hasAsKeyword();

  std::shared_ptr<types::Type> base_type = nullptr;

  if (syntax->getTypeExpression()) {
    std::pair<std::shared_ptr<types::Type>,
              std::unique_ptr<binding::BoundErrorExpression>>
        result = resolveType(syntax->getTypeExpression().get());

    if (result.first == nullptr) {
      return nullptr;
    }
    base_type = result.first;

    if (base_type->isNthg()) {
      m_ctx->reportError(flow_wing::diagnostic::DiagnosticCode::
                             kNthgCannotBeUsedAsParameterType,
                         {}, syntax->getTypeExpression()->getSourceLocation());
      return nullptr;
    }
  } else {
    base_type = Builtins::m_dynamic_type_instance;
  }

  return std::make_shared<types::ParameterType>(
      base_type, getValueKind(has_inout_keyword),
      getTypeConvention(has_as_keyword), getConstness(has_const_keyword));
}

std::vector<std::shared_ptr<types::ReturnType>> TypeResolver::resolveReturnType(
    const syntax::FunctionReturnTypeExpressionSyntax *syntax) {

  if (syntax == nullptr) {
    return {std::make_shared<types::ReturnType>(
        Builtins::m_dynamic_type_instance, types::TypeConvention::kFlowWing)};
  }

  std::vector<std::shared_ptr<types::ReturnType>> return_types;

  const bool has_as_keyword = syntax->hasAsKeyword();

  for (const auto &type_expression : syntax->getTypeExpressions()) {
    auto [base_type, error_expression] = resolveType(type_expression.get());

    return_types.push_back(std::make_shared<types::ReturnType>(
        base_type, getTypeConvention(has_as_keyword)));
  }

  return return_types;
}

std::pair<std::shared_ptr<types::Type>,
          std::unique_ptr<binding::BoundErrorExpression>>
TypeResolver::resolveFunctionType(
    const syntax::FunctionTypeExpressionSyntax *syntax) {
  assert(syntax != nullptr &&
         "TypeResolver::resolveFunctionType: syntax is null");

  std::vector<std::shared_ptr<types::ParameterType>> parameter_types;
  std::vector<std::shared_ptr<types::ReturnType>> return_types;

  size_t parameter_count = 0;
  for (const auto &parameter_type_expression : syntax->getParameterTypes()) {
    const bool has_const_keyword =
        syntax->getConstantKeywordTable().count(parameter_count) > 0;
    const bool has_inout_keyword =
        syntax->getInoutKeywordTable().count(parameter_count) > 0;
    const bool has_as_keyword =
        syntax->getAsParameterKeywordsTable().count(parameter_count) > 0;

    std::shared_ptr<types::Type> parameter_type = nullptr;

    if (!parameter_type_expression) {
      parameter_type = Builtins::m_dynamic_type_instance;
    } else {
      auto [parameter_type, error_expression] =
          resolveType(parameter_type_expression.get());
      if (error_expression != nullptr) {
        return {nullptr, std::move(error_expression)};
      }
    }

    parameter_types.push_back(std::make_shared<types::ParameterType>(
        parameter_type, getValueKind(has_inout_keyword),
        getTypeConvention(has_as_keyword), getConstness(has_const_keyword)));

    parameter_count++;
  }

  const bool has_as_keyword = syntax->hasAsReturnType();

  for (const auto &return_type_expression : syntax->getReturnTypes()) {

    auto [return_type, error_expression] =
        resolveType(return_type_expression.get());

    if (error_expression != nullptr) {
      return {nullptr, std::move(error_expression)};
    }

    return_types.push_back(std::make_shared<types::ReturnType>(
        return_type, getTypeConvention(has_as_keyword)));
  }

  return {std::make_shared<types::FunctionType>(parameter_types, return_types,
                                                -1, false),
          nullptr};
}

} // namespace analysis
} // namespace flow_wing
