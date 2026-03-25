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

#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include <cassert>
#include <vector>
namespace flow_wing {
namespace binding {
std::unique_ptr<BoundExpression> ExpressionBinder::bindContainerExpression(
    syntax::ContainerExpressionSyntax *expression) {

  std::vector<std::unique_ptr<BoundContainerExpressionElement>> elements =
      bindContainerExpressionElements(expression);

  if (elements.empty()) {
    if (auto expected = m_context->peekExpectedType()) {
      if (expected->getKind() == types::TypeKind::kArray) {
        return BinderContext::createDefaultValueExpression(
            expected.get(), expression->getSourceLocation());
      }
    }
    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kEmptyContainerExpression,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{});
    m_context->reportError(error_expression.get());

    return std::move(error_expression);
  }

  for (const auto &element : elements) {

    if (element->getExpression()->getKind() == NodeKind::kErrorExpression) {
      return std::move(element->getExpression());
    }
  }

  // When a fixed 1-D array type is expected (e.g. field `b: TB[2]`), pad
  // missing indices with default values so slots are not left null at runtime.
  {
    const diagnostic::SourceLocation loc = expression->getSourceLocation();
    if (auto expected = m_context->peekExpectedType()) {
      if (expected->getKind() == types::TypeKind::kArray) {
        auto *expected_arr = static_cast<types::ArrayType *>(expected.get());
        const auto &dims = expected_arr->getDimensions();
        if (dims.size() == 1) {
          const size_t need = dims[0];
          if (need > 0) {
            auto underlying = expected_arr->getUnderlyingType();
            std::vector<char> seen(need, 0);
            for (const auto &el : elements) {
              const auto &ix = el->getIndices();
              if (ix.size() == 1 && ix[0] < need) {
                seen[ix[0]] = 1;
              }
            }
            for (size_t i = 0; i < need; ++i) {
              if (seen[i])
                continue;
              auto def = BinderContext::createDefaultValueExpression(
                  underlying.get(), loc);
              if (def->getKind() == NodeKind::kErrorExpression) {
                return def;
              }
              auto elem = std::make_unique<BoundContainerExpressionElement>(
                  std::move(def));
              elem->addIndex(i);
              elements.push_back(std::move(elem));
            }
          }
        }
      }
    }
  }

  size_t initial_depth = 0;
  if (!elements.empty()) {
    initial_depth = elements[0]->getIndices().size();
    // If the first element is itself an array (like 'p'), add its rank
    if (elements[0]->getExpression()->getType()->getKind() ==
        types::TypeKind::kArray) {
      auto arr_type = std::static_pointer_cast<types::ArrayType>(
          elements[0]->getExpression()->getType());
      initial_depth += arr_type->getDimensions().size();
    }
  }

  size_t max_depth = initial_depth;
  size_t min_depth = initial_depth;

  for (const auto &element : elements) {
    size_t current_depth = element->getIndices().size();

    if (element->getExpression()->getType()->getKind() ==
        types::TypeKind::kArray) {
      auto array_type = static_cast<types::ArrayType *>(
          element->getExpression()->getType().get());
      current_depth += array_type->getDimensions().size();
    }

    max_depth = std::max(max_depth, current_depth);
    min_depth = std::min(min_depth, current_depth);
  }

  if (max_depth != min_depth) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kContainerExpressionRankMismatch,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            std::to_string(min_depth), std::to_string(max_depth)});
    m_context->reportError(error_expression.get());

    return std::move(error_expression);
  }

  std::vector<size_t> dimensions(max_depth, 0);

  for (const auto &element : elements) {

    const auto &indices = element->getIndices();
    size_t element_depth = indices.size();

    // Process explicit indices from the container structure
    for (size_t d = 0; d < element_depth && d < max_depth; ++d) {
      if (indices[d] > dimensions[d]) {
        dimensions[d] = indices[d];
      }
    }

    // Process implicit indices from the element's array type if it's an array
    if (element->getExpression()->getType()->getKind() ==
        types::TypeKind::kArray) {
      auto array_type = std::static_pointer_cast<types::ArrayType>(
          element->getExpression()->getType());
      const auto &sub_dims = array_type->getDimensions();

      for (size_t i = 0; i < sub_dims.size(); ++i) {
        size_t current_dim = element_depth + i;
        if (current_dim < max_depth && sub_dims[i] > 0) {
          if (sub_dims[i] - 1 > dimensions[current_dim]) {
            dimensions[current_dim] = sub_dims[i] - 1;
          }
        }
      }
    }
  }

  for (size_t d = 0; d < max_depth; ++d) {
    dimensions[d] += 1;
  }

  auto get_underlying_type = [](std::shared_ptr<types::Type> type) {
    while (type->getKind() == types::TypeKind::kArray) {
      type =
          std::static_pointer_cast<types::ArrayType>(type)->getUnderlyingType();
    }
    return type;
  };

  auto final_element_type =
      get_underlying_type(elements[0]->getExpression()->getType());

  for (size_t i = 1; i < elements.size() && !final_element_type->isDynamic();
       ++i) {
    auto current_type =
        get_underlying_type(elements[i]->getExpression()->getType());

    if (*current_type.get() != *final_element_type.get()) {
      final_element_type = analysis::Builtins::m_dynamic_type_instance;
    }
  }

  auto array_type =
      std::make_shared<types::ArrayType>(final_element_type, dimensions);

  return std::make_unique<BoundContainerExpression>(
      std::move(elements), array_type, false, expression->getSourceLocation());
}

std::vector<std::unique_ptr<BoundContainerExpressionElement>>
ExpressionBinder::bindContainerExpressionElements(
    syntax::ContainerExpressionSyntax *expression) {

  std::vector<std::unique_ptr<BoundContainerExpressionElement>> elements = {};

  if (expression->getValueExpression() == nullptr) {
    return elements;
  }

  auto expressions = bindExpressionList(expression->getValueExpression().get());
  for (size_t i = 0; i < expressions.size(); i++) {

    if (expressions[i]->getKind() == NodeKind::kContainerExpression) {

      auto container_expression =
          static_cast<BoundContainerExpression *>(expressions[i].get());

      size_t nested_elements_size = container_expression->getElements().size();

      for (size_t j = 0; j < nested_elements_size; j++) {
        container_expression->getElements()[j]->addIndex(i);
        elements.push_back(std::move(container_expression->getElements()[j]));
      }

    } else {

      auto element = std::make_unique<BoundContainerExpressionElement>(
          std::move(expressions[i]));
      element->addIndex(i);
      elements.push_back(std::move(element));
    }
  }

  return elements;
}

} // namespace binding
} // namespace flow_wing