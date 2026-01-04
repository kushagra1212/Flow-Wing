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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundColonExpression/BoundColonExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundObjectExpression/BoundObjectExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>
namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression>
ExpressionBinder::bindObjectExpression(syntax::ObjectExpressionSyntax *node) {

  std::map<std::string, std::shared_ptr<types::Type>> field_types_map;
  std::vector<std::unique_ptr<BoundExpression>> colon_expressions;

  if (node->getColonExpression().get()) {
    colon_expressions = bindExpressionList(node->getColonExpression().get());
  }

  for (auto &member : colon_expressions) {
    if (member->getKind() == NodeKind::kErrorExpression) {
      return std::move(member);
    }

    if (member->getKind() != NodeKind::kColonExpression) {

      auto error_expression = std::make_unique<BoundErrorExpression>(
          member->getSourceLocation(),
          diagnostic::DiagnosticCode::kUnexpectedExpression,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              toString(member->getKind()),
              toString(NodeKind::kObjectExpression)});

      m_context->reportError(error_expression.get());

      return std::move(error_expression);
    }

    auto colon_expression = static_cast<BoundColonExpression *>(member.get());

    field_types_map.insert({colon_expression->getFieldName(),
                            colon_expression->getRightExpression()->getType()});
  }

  auto object_type = std::make_shared<types::CustomObjectType>(
      "object_expression", field_types_map);

  return std::make_unique<BoundObjectExpression>(
      std::move(field_types_map), std::move(colon_expressions), object_type,
      node->getSourceLocation());

} // namespace binding
} // namespace binding
} // namespace flow_wing