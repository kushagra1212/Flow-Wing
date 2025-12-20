#pragma once

#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"

namespace flow_wing {
namespace ir_gen {

class IRGenerator : public visitor::BoundTreeVisitor {
public:
  IRGenerator(IRGenContext &ir_gen_context);
  void generate();

  void visit(binding::BoundCompilationUnit *compilation_unit) override;
  void visit(binding::BoundBlockStatement *block_statement) override;
  void visit(binding::BoundExposeStatement *expose_statement) override;
  void visit(binding::BoundCustomTypeStatement *custom_type_statement) override;
  void visit(binding::BoundVariableDeclaration *variable_declaration) override;
  void visit(binding::BoundFunctionStatement *variable_declaration) override;
  void visit(binding::BoundIfStatement *variable_declaration) override;
  void visit(binding::BoundWhileStatement *variable_declaration) override;
  void visit(binding::BoundForStatement *variable_declaration) override;
  void visit(binding::BoundBreakStatement *variable_declaration) override;
  void visit(binding::BoundContinueStatement *variable_declaration) override;
  void visit(binding::BoundReturnStatement *variable_declaration) override;
  void visit(binding::BoundSwitchStatement *variable_declaration) override;
  void visit(binding::BoundClassStatement *variable_declaration) override;
  void visit(binding::BoundIdentifierExpression *variable_declaration) override;
  void visit(binding::BoundIndexExpression *variable_declaration) override;
  void
  visit(binding::BoundIntegerLiteralExpression *variable_declaration) override;
  void
  visit(binding::BoundDoubleLiteralExpression *variable_declaration) override;
  void
  visit(binding::BoundFloatLiteralExpression *variable_declaration) override;
  void visit(
      binding::BoundCharacterLiteralExpression *variable_declaration) override;
  void
  visit(binding::BoundStringLiteralExpression *variable_declaration) override;
  void
  visit(binding::BoundBooleanLiteralExpression *variable_declaration) override;
  void visit(binding::BoundTemplateStringLiteralExpression
                 *variable_declaration) override;
  void visit(binding::BoundErrorStatement *variable_declaration) override;
  void visit(binding::BoundErrorExpression *variable_declaration) override;
  void visit(binding::BoundCallExpression *variable_declaration) override;
  void visit(binding::BoundTernaryExpression *variable_declaration) override;
  void visit(binding::BoundNewExpression *variable_declaration) override;
  void visit(binding::BoundUnaryExpression *variable_declaration) override;
  void visit(binding::BoundBinaryExpression *variable_declaration) override;
  void visit(binding::BoundAssignmentExpression *variable_declaration) override;
  void visit(binding::BoundExpressionStatement *variable_declaration) override;
  void
  visit(binding::BoundModuleAccessExpression *variable_declaration) override;
  void
  visit(binding::BoundMemberAccessExpression *variable_declaration) override;
  void
  visit(binding::BoundNirastLiteralExpression *variable_declaration) override;

  void clearLastValue() { m_last_value = nullptr; }

private:
  IRGenContext &m_ir_gen_context;
  llvm::Value *m_last_value = nullptr;

  llvm::Function *createEntryPointFunction();
  llvm::Value *convertToString(llvm::Value *value, llvm::Type *type);
  llvm::Value *getDefaultValue(flow_wing::types::Type *type);
  void handleReturn();
  void verifyModule();
};
} // namespace ir_gen
} // namespace flow_wing