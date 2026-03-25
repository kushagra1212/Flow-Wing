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

#include "DeclarationAnalyzer.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"

namespace flow_wing {
namespace analysis {

DeclarationAnalyzer::DeclarationAnalyzer(binding::BinderContext &binder_context)
    : m_binder_context(binder_context) {}

void DeclarationAnalyzer::analyze() {
  m_binder_context.getCompilationContext().getAst()->accept(this);
}

// --- Visitation Methods ---

void analysis::DeclarationAnalyzer::visit(syntax::CompilationUnitSyntax *node) {
  for (const auto &statement : node->getStatements()) {
    statement->accept(this);
  }
}

void analysis::DeclarationAnalyzer::visit(syntax::ExposeStatementSyntax *node) {
  // Keep in sync with ExposeStatementBinder: analyze wrapped declarations so
  // symbol tables / class metadata match what binding expects (expose class was
  // previously skipped, which could leave inconsistent state and crash IR/sem).
  auto *inner = node->getStatement().get();
  switch (inner->getKind()) {
  case syntax::NodeKind::kFunctionStatement:
  case syntax::NodeKind::kClassStatement:
  case syntax::NodeKind::kVariableDeclaration:
  case syntax::NodeKind::kCustomTypeStatement:
    inner->accept(this);
    break;
  default:
    break;
  }
}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ErrorExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::BinaryExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::SyntaxToken *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::IdentifierExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ParameterExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::DimensionClauseExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::IntegerLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::Int64LiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::AssignmentExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::BooleanLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::BracketedExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::CallExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::CharacterLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ContainerExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::DeclaratorExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::DoubleLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::FieldDeclarationSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::FillExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::FloatLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::FunctionReturnTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::IndexExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::MemberAccessExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ModuleAccessExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::NewExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::NirastExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::SuperExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ObjectExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ColonExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ParenthesizedExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::StringLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::TemplateStringLiteralExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::TernaryExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::FunctionTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ArrayTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::BoolTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::Deci32TypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::DeciTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::Int8TypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::CharTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::Int32TypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::Int64TypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ModuleAccessTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::NthgTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ObjectTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::StrTypeExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::UnaryExpressionSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::BlockStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::BreakStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::CaseStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ClassStatementSyntax *node) {
  auto *name_expr = static_cast<syntax::IdentifierExpressionSyntax *>(
      node->getClassNameIdentifierExpr().get());
  const auto &class_name = name_expr->getValue();

  std::shared_ptr<types::ClassType> parent_class_type = nullptr;
  if (node->getParentClassIdentifierExpr()) {
    auto &parent_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(
            node->getParentClassIdentifierExpr().get())
            ->getValue();
    auto parent_sym =
        m_binder_context.getSymbolTable()->lookup(parent_name);
    if (parent_sym && parent_sym->getKind() == analysis::SymbolKind::kClass) {
      parent_class_type =
          std::dynamic_pointer_cast<types::ClassType>(parent_sym->getType());
    }
  }

  auto class_type =
      std::make_shared<types::ClassType>(class_name, parent_class_type);
  auto class_symbol = std::make_shared<analysis::Symbol>(
      class_name, analysis::SymbolKind::kClass, class_type);
  if (!m_binder_context.getSymbolTable()->define(class_symbol)) {
    m_binder_context.recordDuplicateClassDeclaration(class_name);
  }
}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ContinueStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::DefaultCaseStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ElseClauseSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ForStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::IfStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(syntax::ModuleStatementSyntax *node) {
  auto *name_expr = static_cast<syntax::IdentifierExpressionSyntax *>(
      node->getModuleNameExpression().get());
  const std::string &module_name = name_expr->getValue();

  auto module_table = std::make_shared<analysis::ScopedSymbolTable>();
  analysis::Builtins::registerIntoSymbolTable(module_table);

  auto module_symbol =
      std::make_shared<analysis::ModuleSymbol>(module_name, module_table);

  if (!m_binder_context.getSymbolTable()->define(module_symbol)) {
    m_binder_context.reportError(
        flow_wing::diagnostic::DiagnosticCode::kModuleAlreadyDeclared,
        {module_name}, name_expr->getSourceLocation());
    return;
  }

  // Allow qualified access `m::name` from inside this module (module name
  // resolves in the module's symbol table).
  if (!module_table->define(module_symbol)) {
    m_binder_context.reportError(
        flow_wing::diagnostic::DiagnosticCode::kModuleAlreadyDeclared,
        {module_name}, name_expr->getSourceLocation());
    return;
  }

  auto saved = m_binder_context.getSymbolTable();
  m_binder_context.switchSymbolTable(module_table);
  m_binder_context.pushModuleScope(module_name);
  for (const auto &stmt : node->getModuleMemberStatements()) {
    stmt->accept(this);
  }
  m_binder_context.popModuleScope();
  m_binder_context.switchSymbolTable(saved);
}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::OrIfStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ReturnStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::SwitchStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::VariableDeclarationSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::WhileStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ExpressionStatementSyntax *node) {}

} // namespace analysis
} // namespace flow_wing