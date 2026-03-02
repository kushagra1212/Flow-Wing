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

#include "GlobalDeclarationsInitializer.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "llvm/IR/Constant.h"

namespace flow_wing {
namespace ir_gen {

GlobalDeclarationsInitializer::GlobalDeclarationsInitializer(
    IRGenContext &ir_gen_context)
    : m_ir_gen_context(ir_gen_context) {}

void GlobalDeclarationsInitializer::initialize() {
  m_ir_gen_context.getCompilationContext().getBoundTree()->accept(this);
  m_ir_gen_context.storeLLVMIr();
}

void GlobalDeclarationsInitializer::declareFunctions(
    analysis::ScopedSymbolTable *global_symbol_table) {
  global_symbol_table->lookupSymbol(
      [&](const analysis::Symbol *symbol) {
        auto function_symbol =
            static_cast<const analysis::FunctionSymbol *>(symbol);

        // Skip built-in functions as they are not native functions
        if (analysis::Builtins::isBuiltInFunction(function_symbol->getName())) {
          return true;
        }

        auto function_type = static_cast<const types::FunctionType *>(
            function_symbol->getType().get());

        auto llvm_function_type =
            m_ir_gen_context.getTypeBuilder()->convertFunction(function_type);

        auto llvm_function = llvm::Function::Create(
            llvm_function_type,
            function_type->isExternal() ? llvm::Function::ExternalLinkage
                                        : llvm::Function::InternalLinkage,
            function_symbol->getName(), m_ir_gen_context.getLLVMModule());

        size_t arg_idx = 0;
        for (auto &arg : llvm_function->args()) {
          // Get the original FlowWing parameter type
          auto param_fw_type =
              function_type->getParameterTypes()[arg_idx]->type.get();

          // Sign Extension (SExt) [Sign Extension is a way to convert a smaller
          // integer type to a larger integer type while preserving the sign of
          // the original value.]
          if (param_fw_type == analysis::Builtins::m_int8_type_instance.get()) {
            arg.addAttr(llvm::Attribute::SExt);
          }

          arg_idx++;
        }

        CODEGEN_DEBUG_LOG("Declared Function: ", function_symbol->getName());
        return true;
      },
      analysis::SymbolKind::kFunction);
}

void GlobalDeclarationsInitializer::visit(
    binding::BoundCompilationUnit *compilation_unit) {

  const auto &global_symbol_table = compilation_unit->getSymbolTable();

  // Declare Built-in Functions
  declareFunctions(global_symbol_table.get());

  for (const auto &statement : compilation_unit->getStatements()) {
    statement->accept(this);
  }

  CODEGEN_DEBUG_LOG("Global Declarations Initialized", "");
}

// Global Variable Declarations
void GlobalDeclarationsInitializer::visit(
    binding::BoundVariableDeclaration *variable_declaration) {

  CODEGEN_DEBUG_LOG("Visiting Bound Variable Declaration", "");

  auto *module = m_ir_gen_context.getLLVMModule();

  for (const auto &symbol : variable_declaration->getSymbols()) {
    const auto &variable_symbol =
        static_cast<const analysis::VariableSymbol *>(symbol.get());

    auto variable_type = variable_symbol->getType().get();
    auto llvm_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(variable_type);

    CODEGEN_DEBUG_LOG("Variable Type", variable_type->getName());

    assert(llvm_type && "LLVM type is null");

    // Already handled in SemanticAnalyzer
    bool is_llvm_constant = false;

    llvm::Constant *default_value =
        m_ir_gen_context.getDefaultValue(variable_type, true);

    if (variable_type->getKind() == types::TypeKind::kObject ||
        variable_type->getKind() == types::TypeKind::kArray) {
      llvm_type = llvm_type->getPointerTo();
      default_value = llvm::ConstantPointerNull::get(llvm_type->getPointerTo());
    }

    auto globalVar = new llvm::GlobalVariable(
        *module, llvm_type, is_llvm_constant,
        llvm::GlobalValue::InternalLinkage, // Internal = private to this module
        default_value,                      // Initializer: 0, 0.0, or null
        variable_symbol->getName());

    m_ir_gen_context.setSymbol(variable_symbol->getName(), globalVar);

    CODEGEN_DEBUG_LOG("Global Variable Declared", variable_symbol->getName());
  }
}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundNewExpression *new_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBlockStatement *block_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundExposeStatement *expose_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundCustomTypeStatement *custom_type_statement) {
}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundFunctionStatement *function_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIfStatement *if_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundWhileStatement *while_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundForStatement *for_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBreakStatement *break_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundContinueStatement *continue_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundReturnStatement *return_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundSwitchStatement *switch_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundClassStatement *class_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIdentifierExpression
        *identifier_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIndexExpression *index_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundIntegerLiteralExpression
        *integer_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundContainerExpression *container_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundDoubleLiteralExpression
        *double_literal_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundStringLiteralExpression
        *string_literal_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBooleanLiteralExpression
        *boolean_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundFloatLiteralExpression
        *float_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundCharacterLiteralExpression
        *character_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundTemplateStringLiteralExpression
        *template_string_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundErrorStatement *error_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundErrorExpression *error_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundCallExpression *call_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundTernaryExpression *ternary_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundUnaryExpression *unary_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundBinaryExpression *binary_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundAssignmentExpression
        *assignment_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundExpressionStatement *expression_statement) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundModuleAccessExpression
        *module_access_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundMemberAccessExpression
        *member_access_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundNirastLiteralExpression
        *nirast_literal_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundParenthesizedExpression
        *parenthesized_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundObjectExpression *object_expression) {}

void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundColonExpression *colon_expression) {}
void GlobalDeclarationsInitializer::visit(
    [[maybe_unused]] binding::BoundDimensionClauseExpression
        *dimension_clause_expression) {}

} // namespace ir_gen
} // namespace flow_wing