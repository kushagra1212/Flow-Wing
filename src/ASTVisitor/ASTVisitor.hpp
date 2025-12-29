#pragma once

#include "src/syntax/expression/ExpressionSyntax.h"
namespace flow_wing {

namespace syntax {
class CompilationUnitSyntax;
class IdentifierExpressionSyntax;
class ParameterExpressionSyntax;
class ArrayTypeExpressionSyntax;
class DimensionClauseExpressionSyntax;
class IntegerLiteralExpressionSyntax;
class FunctionTypeExpressionSyntax;
class VariableDeclarationSyntax;
class AssignmentExpressionSyntax;
class BinaryExpressionSyntax;
class BooleanLiteralExpressionSyntax;
class BracketedExpressionSyntax;
class CallExpressionSyntax;
class CharacterLiteralExpressionSyntax;
class ContainerExpressionSyntax;
class DeclaratorExpressionSyntax;
class DoubleLiteralExpressionSyntax;
class FieldDeclarationSyntax;
class FillExpressionSyntax;
class FloatLiteralExpressionSyntax;
class FunctionReturnTypeExpressionSyntax;
class IndexExpressionSyntax;
class MemberAccessExpressionSyntax;
class ModuleAccessExpressionSyntax;
class NewExpressionSyntax;
class NirastExpressionSyntax;
class ObjectExpressionSyntax;
class ObjectMemberSyntax;
class ParenthesizedExpressionSyntax;
class StringLiteralExpressionSyntax;
class TemplateStringLiteralExpressionSyntax;
class TernaryExpressionSyntax;
class BoolTypeExpressionSyntax;
class Deci32TypeExpressionSyntax;
class DeciTypeExpressionSyntax;
class Int8TypeExpressionSyntax;
class Int32TypeExpressionSyntax;
class Int64TypeExpressionSyntax;
class CharTypeExpressionSyntax;
class ModuleAccessTypeExpressionSyntax;
class NthgTypeExpressionSyntax;
class ObjectTypeExpressionSyntax;
class StrTypeExpressionSyntax;
class UnaryExpressionSyntax;
class ExposeStatementSyntax;
class BlockStatementSyntax;
class FunctionStatementSyntax;
class BreakStatementSyntax;
class BringStatementSyntax;
class CaseStatementSyntax;
class ClassStatementSyntax;
class ContinueStatementSyntax;
class CustomTypeStatementSyntax;
class DefaultCaseStatementSyntax;
class ElseClauseSyntax;
class ForStatementSyntax;
class IfStatementSyntax;
class ModuleStatementSyntax;
class OrIfStatementSyntax;
class ReturnStatementSyntax;
class SwitchStatementSyntax;
class WhileStatementSyntax;
class ExpressionStatementSyntax;
class SyntaxToken;
class ErrorExpressionSyntax;
} // namespace syntax

namespace visitor {

class ASTVisitor {
public:
  virtual ~ASTVisitor() = default;

  virtual void visit(syntax::SyntaxToken *node) = 0;

  virtual void visit(syntax::CompilationUnitSyntax *node) = 0;
  virtual void visit(syntax::IdentifierExpressionSyntax *node) = 0;
  virtual void visit(syntax::ParameterExpressionSyntax *node) = 0;
  virtual void visit(syntax::DimensionClauseExpressionSyntax *node) = 0;
  virtual void visit(syntax::IntegerLiteralExpressionSyntax *node) = 0;

  virtual void visit(syntax::AssignmentExpressionSyntax *node) = 0;
  virtual void visit(syntax::BooleanLiteralExpressionSyntax *node) = 0;
  virtual void visit(syntax::BracketedExpressionSyntax *node) = 0;
  virtual void visit(syntax::CallExpressionSyntax *node) = 0;
  virtual void visit(syntax::CharacterLiteralExpressionSyntax *node) = 0;
  virtual void visit(syntax::ContainerExpressionSyntax *node) = 0;
  virtual void visit(syntax::DeclaratorExpressionSyntax *node) = 0;
  virtual void visit(syntax::DoubleLiteralExpressionSyntax *node) = 0;
  virtual void visit(syntax::FieldDeclarationSyntax *node) = 0;
  virtual void visit(syntax::FillExpressionSyntax *node) = 0;
  virtual void visit(syntax::FloatLiteralExpressionSyntax *node) = 0;
  virtual void visit(syntax::FunctionReturnTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::IndexExpressionSyntax *node) = 0;
  virtual void visit(syntax::MemberAccessExpressionSyntax *node) = 0;
  virtual void visit(syntax::ModuleAccessExpressionSyntax *node) = 0;
  virtual void visit(syntax::NewExpressionSyntax *node) = 0;
  virtual void visit(syntax::NirastExpressionSyntax *node) = 0;
  virtual void visit(syntax::ObjectExpressionSyntax *node) = 0;
  virtual void visit(syntax::ObjectMemberSyntax *node) = 0;
  virtual void visit(syntax::ParenthesizedExpressionSyntax *node) = 0;
  virtual void visit(syntax::StringLiteralExpressionSyntax *node) = 0;
  virtual void visit(syntax::TemplateStringLiteralExpressionSyntax *node) = 0;
  virtual void visit(syntax::TernaryExpressionSyntax *node) = 0;
  virtual void visit(syntax::BinaryExpressionSyntax *node) = 0;
  virtual void visit(syntax::ErrorExpressionSyntax *node) = 0;

  // --- Type Expressions ---
  virtual void visit(syntax::ArrayTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::BoolTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::Deci32TypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::DeciTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::FunctionTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::Int8TypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::CharTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::Int32TypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::Int64TypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::ModuleAccessTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::NthgTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::ObjectTypeExpressionSyntax *node) = 0;
  virtual void visit(syntax::StrTypeExpressionSyntax *node) = 0;

  virtual void visit(syntax::UnaryExpressionSyntax *node) = 0;

  // --- Statements ---
  virtual void visit(syntax::ExposeStatementSyntax *node) = 0;
  virtual void visit(syntax::BlockStatementSyntax *node) = 0;
  virtual void visit(syntax::FunctionStatementSyntax *node) = 0;
  virtual void visit(syntax::BreakStatementSyntax *node) = 0;
  virtual void visit(syntax::BringStatementSyntax *node) = 0;
  virtual void visit(syntax::CaseStatementSyntax *node) = 0;
  virtual void visit(syntax::ClassStatementSyntax *node) = 0;
  virtual void visit(syntax::ContinueStatementSyntax *node) = 0;
  virtual void visit(syntax::CustomTypeStatementSyntax *node) = 0;
  virtual void visit(syntax::DefaultCaseStatementSyntax *node) = 0;
  virtual void visit(syntax::ElseClauseSyntax *node) = 0;
  virtual void visit(syntax::ForStatementSyntax *node) = 0;
  virtual void visit(syntax::IfStatementSyntax *node) = 0;
  virtual void visit(syntax::ModuleStatementSyntax *node) = 0;
  virtual void visit(syntax::OrIfStatementSyntax *node) = 0;
  virtual void visit(syntax::ReturnStatementSyntax *node) = 0;
  virtual void visit(syntax::SwitchStatementSyntax *node) = 0;
  virtual void visit(syntax::VariableDeclarationSyntax *node) = 0;
  virtual void visit(syntax::WhileStatementSyntax *node) = 0;
  virtual void visit(syntax::ExpressionStatementSyntax *node) = 0;
};

} // namespace visitor
} // namespace flow_wing