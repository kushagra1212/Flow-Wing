/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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


#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "IRGenerator.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenContext/IRGenContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundCharacterLiteralExpression/BoundCharacterLiteralExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundFloatLiteralExpression/BoundFloatLiteralExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"

// clang-format off
#include "src/compiler/diagnostics/DiagnosticPush.hpp"
#include "llvm-c/Analysis.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "src/compiler/diagnostics/DiagnosticPop.hpp"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
// clang-format on

namespace flow_wing {
namespace ir_gen {

IRGenerator::IRGenerator(IRGenContext &ir_gen_context)
    : m_ir_gen_context(ir_gen_context) {}

void IRGenerator::generate() {
  m_ir_gen_context.getCompilationContext().getBoundTree()->accept(this);
  m_ir_gen_context.storeLLVMIr();
}

llvm::Function *IRGenerator::createEntryPointFunction() {

  llvm::Type *intType =
      llvm::Type::getInt32Ty(*m_ir_gen_context.getLLVMContext());
  llvm::Type *charType =
      llvm::Type::getInt8Ty(*m_ir_gen_context.getLLVMContext());
  llvm::Type *charPtrType = charType->getPointerTo(); // i8* (char*)
  llvm::Type *argvType = charPtrType->getPointerTo(); // i8** (char**)

  auto function_type =
      llvm::FunctionType::get(intType, {intType, argvType}, false);

  return llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                                constants::functions::kMain_fn.data(),
                                m_ir_gen_context.getLLVMModule());
}

void IRGenerator::handleReturn() {

  auto return_block = m_ir_gen_context.createBlock("return");
  m_ir_gen_context.createBranch(return_block);
  m_ir_gen_context.setInsertPoint(return_block);
  m_ir_gen_context.getLLVMBuilder()->CreateRet(llvm::ConstantInt::get(
      llvm::Type::getInt32Ty(*m_ir_gen_context.getLLVMContext()), 0));
}

void IRGenerator::verifyModule() {
  char **output_message = nullptr;
  LLVMVerifyModule(wrap(m_ir_gen_context.getLLVMModule()),
                   LLVMVerifierFailureAction::LLVMAbortProcessAction,
                   output_message);

  const flow_wing::diagnostic::SourceLocation source_location =
      m_ir_gen_context.getCompilationContext()
          .getBoundTree()
          ->getSourceLocation();

  if (output_message) {
    m_ir_gen_context.reportError(
        flow_wing::diagnostic::DiagnosticCode::kInternalIRGenerationError,
        {flow_wing::diagnostic::DiagnosticArg(*output_message)},
        source_location);
  }
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCompilationUnit *compilation_unit) {

  CODEGEN_DEBUG_LOG("Visiting Bound Compilation Unit", "IR GENERATION");

  auto entry_point_function = createEntryPointFunction();
  auto entry_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "entry", entry_point_function);
  m_ir_gen_context.setInsertPoint(entry_block);
  m_ir_gen_context.pushScope();

  for (const auto &statement : compilation_unit->getStatements()) {
    statement->accept(this);
  }

  m_ir_gen_context.popScope();

  handleReturn();
  CODEGEN_DEBUG_LOG("Verifying Entry Point Function", "IR GENERATION");
  llvm::verifyFunction(*entry_point_function);
  verifyModule();
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundBlockStatement *block_statement) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundExposeStatement *expose_statement) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCustomTypeStatement *custom_type_statement) {
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundVariableDeclaration *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundFunctionStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundIfStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundWhileStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundForStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundBreakStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundContinueStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundReturnStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundSwitchStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundClassStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundIdentifierExpression *variable_declaration) {
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundIndexExpression *variable_declaration) {}
void IRGenerator::visit([[maybe_unused]] binding::BoundIntegerLiteralExpression
                            *variable_declaration) {}

void IRGenerator::visit([[maybe_unused]] binding::BoundDoubleLiteralExpression
                            *variable_declaration) {}
void IRGenerator::visit([[maybe_unused]] binding::BoundStringLiteralExpression
                            *variable_declaration) {}
void IRGenerator::visit([[maybe_unused]] binding::BoundBooleanLiteralExpression
                            *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundTemplateStringLiteralExpression
        *variable_declaration) {}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundErrorStatement *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundErrorExpression *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCallExpression *call_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Call Expression", "IR GENERATION");

  auto function_symbol = call_expression->getSymbol();

  if (analysis::Builtins::isBuiltInFunction(function_symbol->getName())) {

    CODEGEN_DEBUG_LOG("Visiting Built-In Function: ",
                      function_symbol->getName());

    if (function_symbol->getType()->getName() ==
        std::string(ir_gen::constants::functions::kPrintf_fn)) {
      auto printf_function = m_ir_gen_context.getLLVMModule()->getFunction(
          std::string(ir_gen::constants::functions::kPrintf_fn));

      m_ir_gen_context.getLLVMBuilder()->CreateCall(printf_function, {});
    }
  }
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundTernaryExpression *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundNewExpression *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundUnaryExpression *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundBinaryExpression *variable_declaration) {}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundAssignmentExpression *variable_declaration) {
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundExpressionStatement *expression_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Expression Statement", "IR GENERATION");

  expression_statement->getExpression()->accept(this);
}
void IRGenerator::visit([[maybe_unused]] binding::BoundModuleAccessExpression
                            *variable_declaration) {}
void IRGenerator::visit([[maybe_unused]] binding::BoundMemberAccessExpression
                            *variable_declaration) {}
void IRGenerator::visit([[maybe_unused]] binding::BoundNirastLiteralExpression
                            *variable_declaration) {}

void IRGenerator::visit([[maybe_unused]] binding::BoundFloatLiteralExpression
                            *variable_declaration) {}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCharacterLiteralExpression
        *variable_declaration) {}

} // namespace ir_gen
} // namespace flow_wing