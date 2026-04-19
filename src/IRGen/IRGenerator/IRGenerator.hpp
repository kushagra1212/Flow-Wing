#pragma once

#include "src/BoundTreeVisitor/BoundTreeVisitor.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/common/types/Type.hpp"
#include "llvm/IR/Value.h"

namespace llvm {
class StructType;
}

namespace flow_wing {
namespace types {
class ClassType;
}
namespace binding {
class BoundModuleStatement;
}
namespace ir_gen {

class IRGenerator : public visitor::BoundTreeVisitor {
public:
  IRGenerator(IRGenContext &ir_gen_context);
  void generate();

  void visit(binding::BoundCompilationUnit *compilation_unit) override;
  void visit(binding::BoundBlockStatement *block_statement) override;
  void visit(binding::BoundExposeStatement *expose_statement) override;
  void visit(binding::BoundCustomTypeStatement *custom_type_statement) override;
  void visit(binding::BoundVariableDeclaration *variable_declaration_statement)
      override;
  void visit(binding::BoundFunctionStatement *function_statement) override;
  void visit(binding::BoundIfStatement *if_statement) override;
  void visit(binding::BoundWhileStatement *while_statement) override;
  void visit(binding::BoundForStatement *for_statement) override;
  void visit(binding::BoundBreakStatement *break_statement) override;
  void visit(binding::BoundContinueStatement *continue_statement) override;
  void visit(binding::BoundReturnStatement *return_statement) override;
  void visit(binding::BoundSwitchStatement *switch_statement) override;
  void visit(binding::BoundClassStatement *class_statement) override;
  void visit(binding::BoundModuleStatement *module_statement) override;
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
  void visit(binding::BoundDynLiteralExpression *dyn_literal_expression) override;
  void visit(binding::BoundColonExpression *colon_expression) override;
  void visit(binding::BoundContainerExpression *container_expression) override;
  void visit(binding::BoundDimensionClauseExpression
                 *dimension_clause_expression) override;

  llvm::Value *resolvePtr(llvm::Value *value, types::Type *type);

  void clearLast() {
    m_last_value = nullptr;
    m_last_llvm_type = nullptr;
    m_last_type = nullptr;
  }

private:
  IRGenContext &m_ir_gen_context;
  llvm::Value *m_last_value = nullptr;
  llvm::Type *m_last_llvm_type = nullptr;
  types::Type *m_last_type = nullptr;

  llvm::Function *createEntryPointFunction();
  llvm::Value *convertToString(llvm::Value *value, llvm::Type *type,
                               bool is_char = false);
  llvm::Value *convertToBool(llvm::Value *value, llvm::Type *type);
  llvm::Value *getConditionAsBool(llvm::Value *value, types::Type *type);
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

  llvm::Value *emitStructuralComparison(llvm::Value *lhs_ptr,
                                        llvm::Value *rhs_ptr,
                                        types::CustomObjectType *type);

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

  void emitTypedStore(llvm::Value *target_addr, types::Type *target_type,
                      llvm::Value *source_raw_value, types::Type *source_type);
  void emitStructuralCopy(llvm::Value *dest_ptr,
                          types::CustomObjectType *dest_type,
                          llvm::Value *src_ptr,
                          types::CustomObjectType *src_type);
  void emitArrayCopy(llvm::Value *dest_ptr, types::ArrayType *dest_type,
                     llvm::Value *src_ptr, types::ArrayType *src_type);

  void emitClassInstanceFieldInitializers(types::ClassType *root_class,
                                          llvm::StructType *struct_type,
                                          llvm::Value *heap_ptr);
  void emitClassInstanceFieldInitializersImpl(types::ClassType *root_class,
                                              types::ClassType *level,
                                              llvm::StructType *struct_type,
                                              llvm::Value *heap_ptr);

  void handleReturn();
  void verifyModule();

  void emitGlobalVariableForScriptAnchor();
  std::string unescapeString(const std::string &value);

  // Dynamic Result
  llvm::Value *ensureDynamic(llvm::Value *value, types::Type *type);
  llvm::Value *ensurePointer(llvm::Value *value, types::Type *type,
                             const std::string &name_suffix = "");
  uint32_t getRuntimeOpCode(lexer::TokenKind kind);

  // CallExpression Handlers
  void
  dispatchBuiltinFunctionCall(binding::BoundCallExpression *call_expression);
  void dispatchUserDefinedOrExternalFunctionCall(
      binding::BoundCallExpression *call_expression);
  void emitRecursivePrint(llvm::Value *value, types::Type *type,
                          bool is_nested);
  void emitPrint(binding::BoundCallExpression *call_expression);
  void
  emitCast(binding::BoundCallExpression *call_expression,
           types::Type *target_type,
           std::function<llvm::Value *(llvm::Value *, llvm::Type *)> converter);

  llvm::Function *getOrCreateObjectPrinter(types::CustomObjectType *type);
  llvm::Function *getOrCreateArrayPrinter(types::ArrayType *type);
  llvm::Function *getOrCreateStructCopier(types::CustomObjectType *type);
  llvm::Function *getOrCreateStructComparator(types::CustomObjectType *type);
  llvm::Value *getTempObject(types::Type *dest_type, types::Type *src_type,
                             llvm::Value *src_val);
  llvm::Value *getTempArray(types::Type *dest_type, types::Type *src_type,
                            llvm::Value *src_val);
};
} // namespace ir_gen
} // namespace flow_wing
