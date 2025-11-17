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


#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundForStatement/BoundForStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/StatementBinder/StatementBinder.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/WhileStatementSyntax/WhileStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindForStatement(syntax::ForStatementSyntax *statement) {
  assert(statement != nullptr &&
         "WhileStatementBinder::bind: statement is null");

  auto for_statement = static_cast<syntax::ForStatementSyntax *>(statement);

  auto isForLoopCompatibleType = [](const std::shared_ptr<types::Type> &type) {
    return type == analysis::Builtins::m_int32_type_instance ||
           type == analysis::Builtins::m_int64_type_instance ||
           type == analysis::Builtins::m_dynamic_type_instance;
  };

  auto compatible_type_names =
      analysis::Builtins::m_int32_type_instance->getName() + ", " +
      analysis::Builtins::m_int64_type_instance->getName() + ", " +
      analysis::Builtins::m_dynamic_type_instance->getName();

  m_context->getSymbolTable()->enterScope();

  std::unique_ptr<BoundStatement> bound_for_variable_declaration = nullptr;
  std::unique_ptr<BoundExpression> bound_for_assignment_expression = nullptr;

  if (for_statement->getVariableDeclaration() != nullptr) {
    bound_for_variable_declaration =
        bind(for_statement->getVariableDeclaration().get());

    if (bound_for_variable_declaration->getKind() ==
        NodeKind::kErrorStatement) {
      return bound_for_variable_declaration;
    }
    auto bound_variable_declaration = static_cast<BoundVariableDeclaration *>(
        bound_for_variable_declaration.get());
    auto variable_symbols = bound_variable_declaration->getSymbols();

    if (variable_symbols.size() != 1) {
      m_context->reportError(
          diagnostic::DiagnosticCode::kTooManyDeclaratorsInVariableDeclaration,
          {std::to_string(1), std::to_string(variable_symbols.size())},
          for_statement->getVariableDeclaration()->getSourceLocation());
      return std::make_unique<BoundErrorStatement>(
          for_statement->getVariableDeclaration()->getSourceLocation());
    }

    if (!isForLoopCompatibleType(variable_symbols[0]->getType())) {
      m_context->reportError(
          diagnostic::DiagnosticCode::
              kInvalidVariableDeclarationTypeForForLoopVariableDeclaration,
          {compatible_type_names, variable_symbols[0]->getType()->getName()},
          for_statement->getVariableDeclaration()->getSourceLocation());
      return std::make_unique<BoundErrorStatement>(
          for_statement->getVariableDeclaration()->getSourceLocation());
    }
  } else {
    bound_for_assignment_expression = m_expression_binder->bind(
        for_statement->getAssignmentExpression().get());

    if (bound_for_assignment_expression->getKind() ==
        NodeKind::kErrorExpression) {
      return std::make_unique<BoundErrorStatement>(
          for_statement->getAssignmentExpression()->getSourceLocation());
    }

    auto bound_assignment_expression = static_cast<BoundAssignmentExpression *>(
        bound_for_assignment_expression.get());
    auto is_multi_target_assignment =
        bound_assignment_expression->isMultiTargetAssignment();

    if (is_multi_target_assignment) {
      m_context->reportError(
          diagnostic::DiagnosticCode::
              kMultiTargetAssignmentNotAllowedForForLoopAssignmentExpression,
          {}, for_statement->getAssignmentExpression()->getSourceLocation());
      return std::make_unique<BoundErrorStatement>(
          for_statement->getAssignmentExpression()->getSourceLocation());
    }

    auto assignment_expression_type = bound_assignment_expression->getType();

    if (!isForLoopCompatibleType(assignment_expression_type)) {
      m_context->reportError(
          diagnostic::DiagnosticCode::
              kInvalidAssignmentExpressionTypeForForLoopAssignmentExpression,
          {compatible_type_names, assignment_expression_type->getName()},
          for_statement->getAssignmentExpression()->getSourceLocation());
      return std::make_unique<BoundErrorStatement>(
          for_statement->getAssignmentExpression()->getSourceLocation());
    }
  }

  auto bound_upper_bound =
      m_expression_binder->bind(for_statement->getUpperBound().get());

  if (bound_upper_bound->getKind() == NodeKind::kErrorExpression) {
    return std::make_unique<BoundErrorStatement>(
        for_statement->getUpperBound()->getSourceLocation());
  }

  if (!isForLoopCompatibleType(bound_upper_bound->getType())) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kInvalidUpperBoundTypeForForLoop,
        {compatible_type_names, bound_upper_bound->getType()->getName()},
        for_statement->getUpperBound()->getSourceLocation());
    return std::make_unique<BoundErrorStatement>(
        for_statement->getUpperBound()->getSourceLocation());
  }

  auto bound_step = m_expression_binder->bind(for_statement->getStep().get());

  if (bound_step->getKind() == NodeKind::kErrorExpression) {
    return std::make_unique<BoundErrorStatement>(
        for_statement->getStep()->getSourceLocation());
  }

  if (!isForLoopCompatibleType(bound_step->getType())) {
    m_context->reportError(
        diagnostic::DiagnosticCode::kInvalidStepTypeForForLoop,
        {compatible_type_names, bound_step->getType()->getName()},
        for_statement->getStep()->getSourceLocation());
    return std::make_unique<BoundErrorStatement>(
        for_statement->getStep()->getSourceLocation());
  }

  auto bound_for_loop_statement = bind(for_statement->getBody().get());

  if (bound_for_loop_statement->getKind() == NodeKind::kErrorStatement) {
    return bound_for_loop_statement;
  }

  m_context->getSymbolTable()->leaveScope();

  return std::make_unique<BoundForStatement>(
      std::move(bound_for_variable_declaration),
      std::move(bound_for_assignment_expression), std::move(bound_upper_bound),
      std::move(bound_step), std::move(bound_for_loop_statement),
      for_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing