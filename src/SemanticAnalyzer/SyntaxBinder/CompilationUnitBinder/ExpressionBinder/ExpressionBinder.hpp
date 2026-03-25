#pragma once

#include <memory>
#include <string>
#include <vector>

#include "src/SemanticAnalyzer/BoundExpressions/BoundContainerExpression/BoundContainerExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/expression/ColonExpressionSyntax/ColonExpressionSyntax.h"
// Forward declare all syntax nodes
namespace flow_wing {

namespace types {
class Type;
struct ParameterType;
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

class SuperExpressionSyntax;

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

// -- Object Expression --
class ObjectExpressionSyntax;

// -- Fill Expression ( [n fill x] ) --
class FillExpressionSyntax;

// -- Container Expression --
class ContainerExpressionSyntax;

// -- Dimension Clause Expression --
class DimensionClauseExpressionSyntax;
} // namespace syntax

namespace binding {
class BinderContext;
class BoundErrorExpression;

class ExpressionBinder {
public:
  ExpressionBinder(BinderContext *context);

  std::unique_ptr<BoundExpression> bind(syntax::ExpressionSyntax *expression);

  // --- Helpers
  std::vector<std::unique_ptr<BoundExpression>>
  bindExpressionList(syntax::ExpressionSyntax *expression);

  /// Object literal arguments use the corresponding parameter type as the
  /// struct hint (defaults for missing fields, correct callee layout).
  std::vector<std::unique_ptr<BoundExpression>>
  bindCallArgumentList(
      syntax::ExpressionSyntax *argument_expression,
      const std::vector<std::shared_ptr<types::ParameterType>> &param_types);

  static std::vector<syntax::ExpressionSyntax *>
  flattenCommaExpressionList(syntax::ExpressionSyntax *expression);

private:
  BinderContext *m_context;

  // -- Identifier Expression --
  std::unique_ptr<BoundExpression>
  bindIdentifierExpression(syntax::IdentifierExpressionSyntax *expression);

  std::unique_ptr<BoundExpression>
  bindSuperExpression(syntax::SuperExpressionSyntax *expression);

  // -- Call Expression --

  std::unique_ptr<BoundExpression>
  bindCallExpression(syntax::CallExpressionSyntax *expression);

  /// Base-class `init` call: `super(args)` inside a derived `init` only.
  std::unique_ptr<BoundExpression>
  bindSuperInitCall(syntax::CallExpressionSyntax *expression);

  // -- Member Function Call (obj.method(args)) --
  std::unique_ptr<BoundExpression>
  bindMemberFunctionCall(syntax::CallExpressionSyntax *expression);

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

  // -- Object Expression --
  std::unique_ptr<BoundExpression>
  bindObjectExpression(syntax::ObjectExpressionSyntax *expression);
  std::unique_ptr<BoundExpression>
  bindObjectExpression(syntax::ObjectExpressionSyntax *expression,
                       std::shared_ptr<types::Type> structureTypeHint);

  // -- Fill Expression [n fill elem] --
  std::unique_ptr<BoundExpression>
  bindFillExpression(syntax::FillExpressionSyntax *expression);

  // -- Colon Expression --
  std::unique_ptr<BoundExpression>
  bindColonExpression(syntax::ColonExpressionSyntax *expression);

  // -- Binary Expression --
  std::unique_ptr<BoundExpression>
  bindBinaryExpression(syntax::BinaryExpressionSyntax *expression);

  // -- Assignment Expression --

  std::unique_ptr<BoundExpression>
  bindAssignmentExpression(syntax::AssignmentExpressionSyntax *expression);

  // -- Container Expression --
  std::unique_ptr<BoundExpression>
  bindContainerExpression(syntax::ContainerExpressionSyntax *expression);

  std::vector<std::unique_ptr<binding::BoundContainerExpressionElement>>
  bindContainerExpressionElements(
      syntax::ContainerExpressionSyntax *expression);

  // -- Dimension Clause Expression --
  std::unique_ptr<BoundExpression> bindDimensionClauseExpression(
      syntax::DimensionClauseExpressionSyntax *expression);

  // -- Assignment Expression Helpers --
  const BoundExpression *
  getBaseIdentifierFromMemberAccess(const BoundExpression *expression);
  std::unique_ptr<BoundErrorExpression>
  checkConstantVariableAssignment(const BoundExpression *left_expression,
                                  const diagnostic::SourceLocation &location);
};

} // namespace binding
} // namespace flow_wing