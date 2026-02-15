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


#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundBooleanLiteralExpression/BoundBooleanLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundDoubleLiteralExpression/BoundDoubleLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundNirastLiteralExpression/BoundNirastLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/utils/LogConfig.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> BinderContext::createDefaultValueExpression(
    types::Type *type, const diagnostic::SourceLocation &location) {

  if (*type == *analysis::Builtins::m_int32_type_instance ||
      type->isDynamic()) {
    return std::make_unique<BoundIntegerLiteralExpression>(
        0, analysis::Builtins::m_int32_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_int64_type_instance) {
    return std::make_unique<BoundIntegerLiteralExpression>(
        0, analysis::Builtins::m_int64_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_int8_type_instance) {
    return std::make_unique<BoundIntegerLiteralExpression>(
        0, analysis::Builtins::m_int8_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_deci_type_instance) {
    return std::make_unique<BoundDoubleLiteralExpression>(
        0.0, analysis::Builtins::m_deci_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_deci32_type_instance) {
    return std::make_unique<BoundDoubleLiteralExpression>(
        0.0f, analysis::Builtins::m_deci32_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_bool_type_instance) {
    return std::make_unique<BoundBooleanLiteralExpression>(
        false, analysis::Builtins::m_bool_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_str_type_instance) {
    return std::make_unique<BoundStringLiteralExpression>(
        "", analysis::Builtins::m_str_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_char_type_instance) {
    return std::make_unique<BoundCharacterLiteralExpression>(
        '\0', analysis::Builtins::m_char_type_instance, location);
  }

  if (*type == *analysis::Builtins::m_nirast_type_instance) {
    return std::make_unique<BoundNirastLiteralExpression>(
        analysis::Builtins::m_nirast_type_instance, location);
  }

  if (type->getKind() == types::TypeKind::kObject) {

    std::vector<std::unique_ptr<BoundExpression>> colon_expressions;

    std::map<std::string, std::shared_ptr<types::Type>> field_types_map;
    types::CustomObjectType *custom_object_type =
        static_cast<types::CustomObjectType *>(type);
    for (const auto &[field_name, field_type] :
         custom_object_type->getFieldTypesMap()) {

      BINDER_DEBUG_LOG("Creating default value expression for field: " +
                           field_name + " of type: " + field_type->getName(),
                       "BinderContext");

      std::unique_ptr<BoundExpression> default_value_expression =
          BinderContext::createDefaultValueExpression(
              field_type->getKind() == types::TypeKind::kObject
                  ? analysis::Builtins::m_nirast_type_instance.get()
                  : field_type.get(),
              location);

      std::unique_ptr<BoundColonExpression> colon_expression =
          std::make_unique<BoundColonExpression>(
              field_name, std::move(default_value_expression), location);

      field_types_map.insert(
          {colon_expression->getFieldName(),
           colon_expression->getRightExpression()->getType()});

      colon_expressions.push_back(std::move(colon_expression));
    }

    return std::make_unique<BoundObjectExpression>(
        std::move(field_types_map), std::move(colon_expressions),
        std::make_shared<types::CustomObjectType>(
            custom_object_type->getCustomTypeName(),
            custom_object_type->getFieldTypesMap()),
        location);
  }

  if (type->getKind() == types::TypeKind::kArray) {
    auto array_type = static_cast<types::ArrayType *>(type);
    auto default_value_expression = BinderContext::createDefaultValueExpression(
        array_type->getUnderlyingType().get(), location);

    std::vector<std::unique_ptr<BoundContainerExpressionElement>> elements;

    elements.push_back(std::make_unique<BoundContainerExpressionElement>(
        std::move(default_value_expression)));

    return std::make_unique<BoundContainerExpression>(
        std::move(elements),
        std::make_shared<types::ArrayType>(array_type->getUnderlyingType(),
                                           array_type->getDimensions()),
        true, location);
  }

  assert(false && "Unsupported type [createDefaultValueExpression]");

  return nullptr;
}

} // namespace binding
} // namespace flow_wing