/*
 * Flow-Wing Compiler
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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/types/ArrayType/ArrayType.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/FillExpressionSyntax/FillExpressionSyntax.h"
#include <cstdint>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindFillExpression(
    syntax::FillExpressionSyntax *node) {
  auto size_bound = bind(node->getSizeToFillExpression().get());
  if (size_bound->getKind() == NodeKind::kErrorExpression) {
    return size_bound;
  }

  int64_t n = 0;
  if (size_bound->getKind() == NodeKind::kNumberLiteralExpression) {
    n = static_cast<BoundIntegerLiteralExpression *>(size_bound.get())
            ->getValue();
  } else {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        size_bound->getSourceLocation(),
        diagnostic::DiagnosticCode::kUnexpectedExpression,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            "fill array size", "compile-time integer literal"});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  if (n <= 0) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        node->getSourceLocation(),
        diagnostic::DiagnosticCode::kUnexpectedExpression,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            "fill", "positive size"});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  std::vector<std::unique_ptr<BoundContainerExpressionElement>> elements;
  elements.reserve(static_cast<size_t>(n));

  for (int64_t i = 0; i < n; ++i) {
    auto elem_bound = bind(node->getElementExpression().get());
    if (elem_bound->getKind() == NodeKind::kErrorExpression) {
      return elem_bound;
    }
    auto elem = std::make_unique<BoundContainerExpressionElement>(
        std::move(elem_bound));
    elem->addIndex(static_cast<size_t>(i));
    elements.push_back(std::move(elem));
  }

  auto elem_type = elements[0]->getExpression()->getType();
  auto array_type = std::make_shared<types::ArrayType>(
      elem_type, std::vector<size_t>{static_cast<size_t>(n)});

  return std::make_unique<BoundContainerExpression>(
      std::move(elements), array_type, false, node->getSourceLocation());
}

} // namespace binding
} // namespace flow_wing
