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

#include "AssignmentExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/expression/AssignmentExpressionSyntax/AssignmentExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"

std::unique_ptr<BoundExpression>
AssignmentExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                           ExpressionSyntax *expression) {
  std::string variable_str = "";

  AssignmentExpressionSyntax *assignmentExpression =
      static_cast<AssignmentExpressionSyntax *>(expression);

  if (auto variableExpression = dynamic_cast<VariableExpressionSyntax *>(
          assignmentExpression->getLeftRef().get())) {
    variable_str = variableExpression->getVariableName();
  } else if (auto indexExpression = dynamic_cast<IndexExpressionSyntax *>(
                 assignmentExpression->getLeftRef().get())) {
    variable_str = std::any_cast<std::string>(
        indexExpression->getIndexIdentifierExpressionRef()->getValue());
  } else {

    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {},
                   assignmentExpression->getLeftRef()->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidAssignment));

    return std::move(
        ExpressionBinderFactory::create(
            assignmentExpression->getLeftRef()->getKind())
            ->bindExpression(ctx, assignmentExpression->getLeftRef().get()));
  }

  std::unique_ptr<BoundExpression> boundIdentifierExpression(
      ExpressionBinderFactory::create(
          assignmentExpression->getLeftRef()->getKind())
          ->bindExpression(ctx, assignmentExpression->getLeftRef().get()));

  BinderKindUtils::BoundBinaryOperatorKind op =
      BinderKindUtils::getBinaryOperatorKind(
          assignmentExpression->getOperatorTokenKind());

  if (!ctx->getRootRef()->tryLookupVariable(variable_str)) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {variable_str},
                   assignmentExpression->getLeftRef()->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       InvalidAssignmentToUndeclaredVariable));

    return std::move(boundIdentifierExpression);
  }

  if (ctx->getRootRef()->tryGetVariable(variable_str)->isConst()) {
    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic, {variable_str},
                   assignmentExpression->getLeftRef()->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                       InvalidAssignmentToConstantVariable));

    return std::move(boundIdentifierExpression);
  }

  if (assignmentExpression->getRightRef()) {
    std::unique_ptr<BoundExpression> boundRight = std::move(
        ExpressionBinderFactory::create(
            assignmentExpression->getRightRef()->getKind())
            ->bindExpression(ctx, assignmentExpression->getRightRef().get()));

    return std::make_unique<BoundAssignmentExpression>(
        assignmentExpression->getSourceLocation(),
        ctx->getRootRef()->tryGetVariable(variable_str),
        std::move(boundIdentifierExpression), op, std::move(boundRight),
        assignmentExpression->getNeedDefaultInitialization());
  } else {
    return std::make_unique<BoundAssignmentExpression>(
        assignmentExpression->getSourceLocation(),
        ctx->getRootRef()->tryGetVariable(variable_str),
        std::move(boundIdentifierExpression), op, nullptr,
        assignmentExpression->getNeedDefaultInitialization());
  }
}