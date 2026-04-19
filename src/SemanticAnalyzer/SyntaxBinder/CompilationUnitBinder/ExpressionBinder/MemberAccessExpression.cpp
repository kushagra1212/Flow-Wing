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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundMemberAccessExpression/BoundMemberAccessExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/MemberAccessExpressionSyntax/MemberAccessExpressionSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression> ExpressionBinder::bindMemberAccessExpression(
    syntax::MemberAccessExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "MemberAccessExpressionBinder::bind: expression is null");

  auto left_expression = bind(expression->getLeftExpression().get());

  if (left_expression->getKind() == NodeKind::kErrorExpression) {
    return left_expression;
  }

  auto left_type = left_expression->getType();

  if (left_type->getKind() != types::TypeKind::kObject &&
      left_type->getKind() != types::TypeKind::kClass) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        expression->getLeftExpression()->getSourceLocation(),
        diagnostic::DiagnosticCode::kMemberAccessOnNonObjectVariable,
        diagnostic::DiagnosticArgs{left_type->getName()});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto member_identifier = static_cast<syntax::IdentifierExpressionSyntax *>(
      expression->getRightExpression().get());
  const auto &member_name = member_identifier->getValue();

  std::shared_ptr<types::Type> field_type;

  if (left_type->getKind() == types::TypeKind::kObject) {
    auto object_type = static_cast<types::CustomObjectType *>(left_type.get());
    const auto &field_type_it =
        object_type->getFieldTypesMap().find(member_name);
    if (field_type_it == object_type->getFieldTypesMap().end()) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          member_identifier->getSourceLocation(),
          diagnostic::DiagnosticCode::kMemberNotFoundInObject,
          diagnostic::DiagnosticArgs{member_name, object_type->getName()});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
    field_type = field_type_it->second;
  } else {
    auto class_type = static_cast<types::ClassType *>(left_type.get());
    auto member_symbol = class_type->lookupField(member_name);
    if (!member_symbol) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          member_identifier->getSourceLocation(),
          diagnostic::DiagnosticCode::kMemberNotFoundInObject,
          diagnostic::DiagnosticArgs{member_name, class_type->getName()});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
    if (member_symbol->getKind() != analysis::SymbolKind::kVariable) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          member_identifier->getSourceLocation(),
          diagnostic::DiagnosticCode::kMemberNotFoundInObject,
          diagnostic::DiagnosticArgs{member_name, class_type->getName()});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
    field_type = member_symbol->getType();
  }

  return std::make_unique<BoundMemberAccessExpression>(
      std::move(left_expression), member_name, field_type,
      expression->getSourceLocation());

  /*
     x.y => (x).y

     x.y[0] => (x.y)[0]

     x.y[0].z => ((x.y)[0]).z

     x[0].y.z

     x().y.z

     x().y[0].z


  */
}

} // namespace binding
} // namespace flow_wing