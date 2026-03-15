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

#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundIntegerLiteralExpression/BoundIntegerLiteralExpression.hpp"
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
    return type == analysis::Builtins::m_int8_type_instance ||
           type == analysis::Builtins::m_int32_type_instance ||
           type == analysis::Builtins::m_int64_type_instance ||
           type == analysis::Builtins::m_dynamic_type_instance;
  };

  auto compatible_type_names =
      analysis::Builtins::m_int8_type_instance->getName() + ", " +
      analysis::Builtins::m_int32_type_instance->getName() + ", " +
      analysis::Builtins::m_int64_type_instance->getName() + ", " +
      analysis::Builtins::m_dynamic_type_instance->getName();

  m_context->getSymbolTable()->enterScope();
  m_context->getSymbolTable()->pushBreakScope();

  std::unique_ptr<BoundStatement> bound_for_variable_declaration = nullptr;
  std::unique_ptr<BoundExpression> bound_for_assignment_expression = nullptr;

  if (for_statement->getVariableDeclaration() != nullptr) {
    bound_for_variable_declaration =
        bind(for_statement->getVariableDeclaration().get());

    if (bound_for_variable_declaration->getKind() ==
        NodeKind::kErrorStatement) {
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return bound_for_variable_declaration;
    }
    auto bound_variable_declaration = static_cast<BoundVariableDeclaration *>(
        bound_for_variable_declaration.get());
    auto variable_symbols = bound_variable_declaration->getSymbols();

    if (variable_symbols.size() != 1) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          for_statement->getVariableDeclaration()->getSourceLocation(),
          diagnostic::DiagnosticCode::kTooManyDeclaratorsInVariableDeclaration,
          diagnostic::DiagnosticArgs{std::to_string(1),
                                     std::to_string(variable_symbols.size())});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }

    if (!isForLoopCompatibleType(variable_symbols[0]->getType())) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          for_statement->getVariableDeclaration()->getSourceLocation(),
          diagnostic::DiagnosticCode::
              kInvalidVariableDeclarationTypeForForLoopVariableDeclaration,
          diagnostic::DiagnosticArgs{
              compatible_type_names,
              variable_symbols[0]->getType()->getName()});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }
  } else {
    bound_for_assignment_expression = m_expression_binder->bind(
        for_statement->getAssignmentExpression().get());

    if (bound_for_assignment_expression->getKind() ==
        NodeKind::kErrorExpression) {
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::make_unique<BoundErrorStatement>(
          std::move(bound_for_assignment_expression));
    }

    auto bound_assignment_expression = static_cast<BoundAssignmentExpression *>(
        bound_for_assignment_expression.get());
    auto is_multi_target_assignment =
        bound_assignment_expression->isMultiTargetAssignment();

    if (is_multi_target_assignment) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          for_statement->getAssignmentExpression()->getSourceLocation(),
          diagnostic::DiagnosticCode::
              kMultiTargetAssignmentNotAllowedForForLoopAssignmentExpression,
          diagnostic::DiagnosticArgs{});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }

    auto assignment_expression_type = bound_assignment_expression->getType();

    if (!isForLoopCompatibleType(assignment_expression_type)) {
      auto error_statement = std::make_unique<BoundErrorStatement>(
          for_statement->getAssignmentExpression()->getSourceLocation(),
          diagnostic::DiagnosticCode::
              kInvalidAssignmentExpressionTypeForForLoopAssignmentExpression,
          diagnostic::DiagnosticArgs{compatible_type_names,
                                     assignment_expression_type->getName()});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }
  }

  auto bound_upper_bound =
      m_expression_binder->bind(for_statement->getUpperBound().get());

  if (bound_upper_bound->getKind() == NodeKind::kErrorExpression) {
    m_context->getSymbolTable()->popBreakScope();
    m_context->getSymbolTable()->leaveScope();
    return std::make_unique<BoundErrorStatement>(std::move(bound_upper_bound));
  }

  if (!isForLoopCompatibleType(bound_upper_bound->getType())) {

    auto error_statement = std::make_unique<BoundErrorStatement>(
        for_statement->getUpperBound()->getSourceLocation(),
        diagnostic::DiagnosticCode::kInvalidUpperBoundTypeForForLoop,
        diagnostic::DiagnosticArgs{compatible_type_names,
                                   bound_upper_bound->getType()->getName()});
    m_context->reportError(error_statement.get());
    m_context->getSymbolTable()->popBreakScope();
    m_context->getSymbolTable()->leaveScope();
    return std::move(error_statement);
  }

  std::unique_ptr<BoundExpression> bound_step = nullptr;
  if (for_statement->getStep() != nullptr) {
    bound_step = m_expression_binder->bind(for_statement->getStep().get());

    if (bound_step->getKind() == NodeKind::kErrorExpression) {
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::make_unique<BoundErrorStatement>(std::move(bound_step));
    }

    if (!isForLoopCompatibleType(bound_step->getType())) {

      auto error_statement = std::make_unique<BoundErrorStatement>(
          for_statement->getStep()->getSourceLocation(),
          diagnostic::DiagnosticCode::kInvalidStepTypeForForLoop,
          diagnostic::DiagnosticArgs{compatible_type_names,
                                     bound_step->getType()->getName()});
      m_context->reportError(error_statement.get());
      m_context->getSymbolTable()->popBreakScope();
      m_context->getSymbolTable()->leaveScope();
      return std::move(error_statement);
    }
  } else {
    std::shared_ptr<types::Type> step_type;
    if (bound_for_variable_declaration != nullptr) {
      auto *var_decl = static_cast<BoundVariableDeclaration *>(
          bound_for_variable_declaration.get());
      step_type = var_decl->getSymbols()[0]->getType();
    } else {
      step_type = bound_for_assignment_expression->getType();
    }
    const auto &loc = for_statement->getSourceLocation();
    if (*step_type == *analysis::Builtins::m_int8_type_instance) {
      bound_step = std::make_unique<BoundIntegerLiteralExpression>(
          1, analysis::Builtins::m_int8_type_instance, loc);
    } else if (*step_type == *analysis::Builtins::m_int32_type_instance) {
      bound_step = std::make_unique<BoundIntegerLiteralExpression>(
          1, analysis::Builtins::m_int32_type_instance, loc);
    } else if (*step_type == *analysis::Builtins::m_int64_type_instance) {
      bound_step = std::make_unique<BoundIntegerLiteralExpression>(
          1, analysis::Builtins::m_int64_type_instance, loc);
    } else {
      bound_step = std::make_unique<BoundIntegerLiteralExpression>(
          1, analysis::Builtins::m_dynamic_type_instance, loc);
    }
  }

  auto bound_for_loop_statement = bind(for_statement->getBody().get());

  if (bound_for_loop_statement->getKind() == NodeKind::kErrorStatement) {
    m_context->getSymbolTable()->popBreakScope();
    m_context->getSymbolTable()->leaveScope();
    return bound_for_loop_statement;
  }

  m_context->getSymbolTable()->popBreakScope();
  m_context->getSymbolTable()->leaveScope();

  return std::make_unique<BoundForStatement>(
      std::move(bound_for_variable_declaration),
      std::move(bound_for_assignment_expression), std::move(bound_upper_bound),
      std::move(bound_step), std::move(bound_for_loop_statement),
      for_statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing