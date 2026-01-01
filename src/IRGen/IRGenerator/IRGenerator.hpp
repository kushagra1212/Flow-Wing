#pragma once

#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/common/types/Type.hpp"
#include "llvm/IR/Value.h"

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
  void
  visit(binding::BoundParenthesizedExpression *variable_declaration) override;
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

  void clearLast() {
    m_last_value = nullptr;
    m_last_type = nullptr;
  }

private:
  IRGenContext &m_ir_gen_context;
  llvm::Value *m_last_value = nullptr;
  types::Type *m_last_type = nullptr;

  llvm::Function *createEntryPointFunction();
  llvm::Value *convertToString(llvm::Value *value, llvm::Type *type,
                               bool is_char = false);
  llvm::Value *convertToBool(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToInt8(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToInt32(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToInt64(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToChar(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToDouble(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToFloat(llvm::Value *value, llvm::Type *type);
  llvm::Value *convertToTargetType(llvm::Value *value,
                                   flow_wing::types::Type *target_type,
                                   flow_wing::types::Type *source_type);

  llvm::Value *getBinaryResult(llvm::Value *left_value,
                               llvm::Value *right_value,
                               lexer::TokenKind operator_kind,
                               types::Type *left_type, types::Type *right_type,
                               types::Type *result_type);

  // Boolean Result
  llvm::Value *getBooleanResult(llvm::Value *left_value,
                                llvm::Value *right_value,
                                lexer::TokenKind operator_kind,
                                types::Type *left_type,
                                types::Type *right_type);

  llvm::Value *getEqualityComparisonBoolResult(llvm::Value *left_value,
                                               llvm::Value *right_value,
                                               types::Type *left_type,
                                               types::Type *right_type);
  llvm::Value *getInequalityComparisonBoolResult(llvm::Value *left_value,
                                                 llvm::Value *right_value,
                                                 types::Type *left_type,
                                                 types::Type *right_type);
  llvm::Value *getLogicalAndBoolResult(llvm::Value *left_value,
                                       llvm::Value *right_value,
                                       types::Type *left_type,
                                       types::Type *right_type);
  llvm::Value *getLogicalOrBoolResult(llvm::Value *left_value,
                                      llvm::Value *right_value,
                                      types::Type *left_type,
                                      types::Type *right_type);
  llvm::Value *getLessThanBoolResult(llvm::Value *left_value,
                                     llvm::Value *right_value,
                                     types::Type *left_type,
                                     types::Type *right_type);
  llvm::Value *getLessThanOrEqualBoolResult(llvm::Value *left_value,
                                            llvm::Value *right_value,
                                            types::Type *left_type,
                                            types::Type *right_type);
  llvm::Value *getGreaterThanBoolResult(llvm::Value *left_value,
                                        llvm::Value *right_value,
                                        types::Type *left_type,
                                        types::Type *right_type);
  llvm::Value *getGreaterThanOrEqualBoolResult(llvm::Value *left_value,
                                               llvm::Value *right_value,
                                               types::Type *left_type,
                                               types::Type *right_type);

  llvm::Value *getIntResult(llvm::Value *left_value, llvm::Value *right_value,
                            lexer::TokenKind operator_kind,
                            types::Type *left_type, types::Type *right_type);
  llvm::Value *getInt32Result(llvm::Value *left_value, llvm::Value *right_value,
                              lexer::TokenKind operator_kind,
                              types::Type *left_type, types::Type *right_type);
  llvm::Value *getInt64Result(llvm::Value *left_value, llvm::Value *right_value,
                              lexer::TokenKind operator_kind,
                              types::Type *left_type, types::Type *right_type);
  llvm::Value *getInt8Result(llvm::Value *left_value, llvm::Value *right_value,
                             lexer::TokenKind operator_kind,
                             types::Type *left_type, types::Type *right_type);
  llvm::Value *getCharResult(llvm::Value *left_value, llvm::Value *right_value,
                             lexer::TokenKind operator_kind);
  llvm::Value *getDecimal32Result(llvm::Value *left_value,
                                  llvm::Value *right_value,
                                  lexer::TokenKind operator_kind);
  llvm::Value *getDecimalResult(llvm::Value *left_value,
                                llvm::Value *right_value,
                                lexer::TokenKind operator_kind);
  llvm::Value *getStringResult(llvm::Value *left_value,
                               llvm::Value *right_value,
                               lexer::TokenKind operator_kind,
                               types::Type *left_type, types::Type *right_type);

  llvm::Value *getDynamicBinaryResult(llvm::Value *left_value,
                                      llvm::Value *right_value,
                                      lexer::TokenKind operator_kind,
                                      types::Type *left_type,
                                      types::Type *right_type);
  llvm::Value *getDynamicUnaryResult(llvm::Value *value,
                                     lexer::TokenKind operator_kind,
                                     types::Type *expression_type);

  // Unary Result

  llvm::Value *getUnaryOperationResult(llvm::Value *value,
                                       lexer::TokenKind operator_kind,
                                       types::Type *result_type,
                                       types::Type *expression_type);

  // Integer Result
  llvm::Value *getIntResult(llvm::Value *value, lexer::TokenKind operator_kind);
  llvm::Value *getBoolResult(llvm::Value *value, lexer::TokenKind operator_kind,
                             types::Type *expression_type);
  llvm::Value *getDecimal32Result(llvm::Value *value,
                                  lexer::TokenKind operator_kind);
  llvm::Value *getDecimalResult(llvm::Value *value,
                                lexer::TokenKind operator_kind);

  // Restore
  llvm::Value *resolveValue(llvm::Value *potential_ptr, types::Type *type);

  void handleReturn();
  void verifyModule();

  std::string unescapeString(const std::string &value);

  // Dynamic Result
  llvm::Value *ensureDynamic(llvm::Value *value, types::Type *type);
  uint32_t getRuntimeOpCode(lexer::TokenKind kind);
};
} // namespace ir_gen
} // namespace flow_wing
