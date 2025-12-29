#pragma once

#include <memory>
#include <string>
#include <vector>

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
// Forward declare all syntax nodes
namespace flow_wing {

namespace types {
class Type;
} // namespace types

namespace syntax {
class ExpressionSyntax;
class BinaryExpressionSyntax;
class IdentifierExpressionSyntax;
class CallExpressionSyntax;

// -- Literal Expressions --
class DoubleLiteralExpressionSyntax;
class FloatLiteralExpressionSyntax;
class CharacterLiteralExpressionSyntax;
class StringLiteralExpressionSyntax;
class TemplateStringLiteralExpressionSyntax;
class BooleanLiteralExpressionSyntax;
class IntegerLiteralExpressionSyntax;
class Int64LiteralExpressionSyntax;
// -- Nirast Expressions --
class NirastExpressionSyntax;

// -- Index Expression --
class IndexExpressionSyntax;

// -- Module Access Expression --
class ModuleAccessExpressionSyntax;

// -- Member Access Expression --
class MemberAccessExpressionSyntax;

// -- Ternary Expression --
class TernaryExpressionSyntax;

// -- New Expression --
class NewExpressionSyntax;

// -- Unary Expression --
class UnaryExpressionSyntax;

// -- Binary Expression --
class BinaryExpressionSyntax;

// -- Assignment Expression --
class AssignmentExpressionSyntax;

// -- Parenthesized Expression --
class ParenthesizedExpressionSyntax;
} // namespace syntax

namespace binding {
class BinderContext;

class ExpressionBinder {
public:
  ExpressionBinder(BinderContext *context);

  std::unique_ptr<BoundExpression> bind(syntax::ExpressionSyntax *expression);

  // --- Helpers
  std::vector<std::unique_ptr<BoundExpression>>
  bindExpressionList(syntax::ExpressionSyntax *expression);

private:
  BinderContext *m_context;

  // -- Identifier Expression --
  std::unique_ptr<BoundExpression>
  bindIdentifierExpression(syntax::IdentifierExpressionSyntax *expression);

  // -- Call Expression --

  std::unique_ptr<BoundExpression>
  bindCallExpression(syntax::CallExpressionSyntax *expression);

  // -- Literal Expressions --
  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::IntegerLiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::Int64LiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::DoubleLiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::FloatLiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::CharacterLiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::StringLiteralExpressionSyntax *expression);
  std::unique_ptr<BoundExpression> bindLiteralExpression(
      syntax::TemplateStringLiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::BooleanLiteralExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindLiteralExpression(syntax::NirastExpressionSyntax *expression);

  // -- Index Expression --
  std::unique_ptr<BoundExpression>
  bindIndexExpression(syntax::IndexExpressionSyntax *expression);

  // -- Module Access Expression --
  std::unique_ptr<BoundExpression>
  bindModuleAccessExpression(syntax::ModuleAccessExpressionSyntax *expression);

  // -- Member Access Expression --
  std::unique_ptr<BoundExpression>
  bindMemberAccessExpression(syntax::MemberAccessExpressionSyntax *expression);

  // -- Ternary Expression --
  std::unique_ptr<BoundExpression>
  bindTernaryExpression(syntax::TernaryExpressionSyntax *expression);

  // -- New Expression --
  std::unique_ptr<BoundExpression>
  bindNewExpression(syntax::NewExpressionSyntax *expression);

  // -- Unary Expression --
  std::unique_ptr<BoundExpression>
  bindUnaryExpression(syntax::UnaryExpressionSyntax *expression);

  // -- Helper Methods --
  std::pair<bool, std::shared_ptr<types::Type>>
  isUnaryAllowedType(lexer::TokenKind operator_token_kind,
                     std::shared_ptr<types::Type> type);
  // -- Parenthesized Expression --
  std::unique_ptr<BoundExpression> bindParenthesizedExpression(
      syntax::ParenthesizedExpressionSyntax *expression);

  // -- Binary Expression --
  std::unique_ptr<BoundExpression>
  bindBinaryExpression(syntax::BinaryExpressionSyntax *expression);

  // -- Assignment Expression --

  std::unique_ptr<BoundExpression>
  bindAssignmentExpression(syntax::AssignmentExpressionSyntax *expression);
};

} // namespace binding
} // namespace flow_wing