#pragma once

#include "src/ASTVisitor/ASTVisitor.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"

namespace flow_wing {

namespace analysis {

class DeclarationAnalyzer : public visitor::ASTVisitor {
public:
  DeclarationAnalyzer(binding::BinderContext &binder_context);
  void analyze();

  void visit(syntax::SyntaxToken *node) override;

  void visit(syntax::CompilationUnitSyntax *node) override;
  void visit(syntax::IdentifierExpressionSyntax *node) override;
  void visit(syntax::ParameterExpressionSyntax *node) override;
  void visit(syntax::DimensionClauseExpressionSyntax *node) override;
  void visit(syntax::IntegerLiteralExpressionSyntax *node) override;
  void visit(syntax::Int64LiteralExpressionSyntax *node) override;

  void visit(syntax::AssignmentExpressionSyntax *node) override;
  void visit(syntax::BooleanLiteralExpressionSyntax *node) override;
  void visit(syntax::BracketedExpressionSyntax *node) override;
  void visit(syntax::CallExpressionSyntax *node) override;
  void visit(syntax::CharacterLiteralExpressionSyntax *node) override;
  void visit(syntax::ContainerExpressionSyntax *node) override;
  void visit(syntax::DeclaratorExpressionSyntax *node) override;
  void visit(syntax::DoubleLiteralExpressionSyntax *node) override;
  void visit(syntax::FieldDeclarationSyntax *node) override;
  void visit(syntax::FillExpressionSyntax *node) override;
  void visit(syntax::FloatLiteralExpressionSyntax *node) override;
  void visit(syntax::FunctionReturnTypeExpressionSyntax *node) override;
  void visit(syntax::IndexExpressionSyntax *node) override;
  void visit(syntax::MemberAccessExpressionSyntax *node) override;
  void visit(syntax::ModuleAccessExpressionSyntax *node) override;
  void visit(syntax::NewExpressionSyntax *node) override;
  void visit(syntax::NirastExpressionSyntax *node) override;
  void visit(syntax::ObjectExpressionSyntax *node) override;
  void visit(syntax::ColonExpressionSyntax *node) override;
  void visit(syntax::ParenthesizedExpressionSyntax *node) override;
  void visit(syntax::StringLiteralExpressionSyntax *node) override;
  void visit(syntax::TemplateStringLiteralExpressionSyntax *node) override;
  void visit(syntax::TernaryExpressionSyntax *node) override;
  void visit(syntax::BinaryExpressionSyntax *node) override;
  void visit(syntax::ErrorExpressionSyntax *node) override;

  // --- Type Expressions ---
  void visit(syntax::ArrayTypeExpressionSyntax *node) override;
  void visit(syntax::BoolTypeExpressionSyntax *node) override;
  void visit(syntax::Deci32TypeExpressionSyntax *node) override;
  void visit(syntax::DeciTypeExpressionSyntax *node) override;
  void visit(syntax::FunctionTypeExpressionSyntax *node) override;
  void visit(syntax::Int8TypeExpressionSyntax *node) override;
  void visit(syntax::CharTypeExpressionSyntax *node) override;
  void visit(syntax::Int32TypeExpressionSyntax *node) override;
  void visit(syntax::Int64TypeExpressionSyntax *node) override;
  void visit(syntax::ModuleAccessTypeExpressionSyntax *node) override;
  void visit(syntax::NthgTypeExpressionSyntax *node) override;
  void visit(syntax::ObjectTypeExpressionSyntax *node) override;
  void visit(syntax::StrTypeExpressionSyntax *node) override;

  void visit(syntax::UnaryExpressionSyntax *node) override;

  // --- Statements ---
  void visit(syntax::ExposeStatementSyntax *node) override;
  void visit(syntax::BlockStatementSyntax *node) override;
  void visit(syntax::FunctionStatementSyntax *node) override;
  void visit(syntax::BreakStatementSyntax *node) override;
  void visit(syntax::BringStatementSyntax *node) override;
  void visit(syntax::CaseStatementSyntax *node) override;
  void visit(syntax::ClassStatementSyntax *node) override;
  void visit(syntax::ContinueStatementSyntax *node) override;
  void visit(syntax::CustomTypeStatementSyntax *node) override;
  void visit(syntax::DefaultCaseStatementSyntax *node) override;
  void visit(syntax::ElseClauseSyntax *node) override;
  void visit(syntax::ForStatementSyntax *node) override;
  void visit(syntax::IfStatementSyntax *node) override;
  void visit(syntax::ModuleStatementSyntax *node) override;
  void visit(syntax::OrIfStatementSyntax *node) override;
  void visit(syntax::ReturnStatementSyntax *node) override;
  void visit(syntax::SwitchStatementSyntax *node) override;
  void visit(syntax::VariableDeclarationSyntax *node) override;
  void visit(syntax::WhileStatementSyntax *node) override;
  void visit(syntax::ExpressionStatementSyntax *node) override;

private:
  binding::BinderContext &m_binder_context;

  std::shared_ptr<types::Type>
  inferReturnType(syntax::BlockStatementSyntax *body);
};
} // namespace analysis
} // namespace flow_wing