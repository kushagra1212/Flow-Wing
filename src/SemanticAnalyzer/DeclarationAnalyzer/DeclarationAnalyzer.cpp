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
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/ExposeStatementSyntax/ExposeStatementSyntax.h"

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
  if (node->getStatement()->getKind() == syntax::NodeKind::kFunctionStatement) {
    node->getStatement()->accept(this);
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
    [[maybe_unused]] syntax::ClassStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ContinueStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::CustomTypeStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::DefaultCaseStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ElseClauseSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ForStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::IfStatementSyntax *node) {}

void analysis::DeclarationAnalyzer::visit(
    [[maybe_unused]] syntax::ModuleStatementSyntax *node) {}

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