#pragma once

#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"

namespace flow_wing {
namespace ir_gen {

class GlobalDeclarationsInitializer : public visitor::BoundTreeVisitor {
public:
  GlobalDeclarationsInitializer(IRGenContext &ir_gen_context);
  void initialize();

  void visit(binding::BoundCompilationUnit *compilation_unit) override;
  void visit(binding::BoundBlockStatement *block_statement) override;
  void visit(binding::BoundExposeStatement *expose_statement) override;
  void visit(binding::BoundCustomTypeStatement *custom_type_statement) override;
  void visit(binding::BoundVariableDeclaration *variable_declaration) override;
  void visit(binding::BoundFunctionStatement *variable_declaration) override;
  void visit(binding::BoundIfStatement *if_statement) override;
  void visit(binding::BoundWhileStatement *while_statement) override;
  void visit(binding::BoundForStatement *for_statement) override;
  void visit(binding::BoundBreakStatement *break_statement) override;
  void visit(binding::BoundContinueStatement *continue_statement) override;
  void visit(binding::BoundReturnStatement *return_statement) override;
  void visit(binding::BoundSwitchStatement *switch_statement) override;
  void visit(binding::BoundClassStatement *class_statement) override;
  void
  visit(binding::BoundIdentifierExpression *identifier_expression) override;
  void visit(binding::BoundIndexExpression *index_expression) override;
  void visit(binding::BoundIntegerLiteralExpression *integer_literal_expression)
      override;
  void visit(binding::BoundDoubleLiteralExpression *double_literal_expression)
      override;
  void visit(
      binding::BoundFloatLiteralExpression *float_literal_expression) override;
  void visit(binding::BoundCharacterLiteralExpression
                 *character_literal_expression) override;
  void visit(binding::BoundStringLiteralExpression *string_literal_expression)
      override;
  void visit(binding::BoundBooleanLiteralExpression *boolean_literal_expression)
      override;
  void visit(binding::BoundTemplateStringLiteralExpression
                 *template_string_literal_expression) override;
  void visit(binding::BoundErrorStatement *error_statement) override;
  void visit(binding::BoundErrorExpression *error_expression) override;
  void visit(binding::BoundCallExpression *call_expression) override;
  void visit(binding::BoundTernaryExpression *ternary_expression) override;
  void visit(binding::BoundNewExpression *new_expression) override;
  void visit(
      binding::BoundParenthesizedExpression *parenthesized_expression) override;
  void visit(binding::BoundObjectExpression *object_expression) override;
  void visit(binding::BoundUnaryExpression *unary_expression) override;
  void visit(binding::BoundBinaryExpression *binary_expression) override;
  void
  visit(binding::BoundAssignmentExpression *assignment_expression) override;
  void visit(binding::BoundExpressionStatement *expression_statement) override;
  void visit(
      binding::BoundModuleAccessExpression *module_access_expression) override;
  void visit(
      binding::BoundMemberAccessExpression *member_access_expression) override;
  void visit(binding::BoundNirastLiteralExpression *nirast_literal_expression)
      override;
  void visit(binding::BoundColonExpression *colon_expression) override;

  void visit(binding::BoundContainerExpression *container_expression) override;
  void visit(binding::BoundDimensionClauseExpression
                 *dimension_clause_expression) override;

private:
  IRGenContext &m_ir_gen_context;

  // Declarations
  void declareFunctions(analysis::ScopedSymbolTable *global_symbol_table);
};
} // namespace ir_gen
} // namespace flow_wing