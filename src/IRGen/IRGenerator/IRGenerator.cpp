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
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundStringLiteralExpression/BoundStringLiteralExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/BoundCompilationUnit.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/VariableSymbol.hpp"
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
    [[maybe_unused]] binding::BoundBlockStatement *block_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Block Statement", "IR GENERATION");

  for (const auto &statement : block_statement->getStatements()) {
    statement->accept(this);
    clearLastValue();
  }
}

void IRGenerator::visit([[maybe_unused]] binding::BoundParenthesizedExpression
                            *parenthesized_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Parenthesized Expression", "IR GENERATION");
  parenthesized_expression->getExpression()->accept(this);
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundExposeStatement *expose_statement) {
  assert(false && "Expose statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundCustomTypeStatement *custom_type_statement) {
  assert(false && "Custom type statement not supported");
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundFunctionStatement *statement) {
  assert(false && "Function statement not supported");
}
void IRGenerator::visit([[maybe_unused]] binding::BoundIfStatement *statement) {
  assert(false && "If statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundWhileStatement *statement) {
  assert(false && "While statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundForStatement *statement) {
  assert(false && "For statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundBreakStatement *statement) {
  assert(false && "Break statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundContinueStatement *statement) {
  assert(false && "Continue statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundReturnStatement *statement) {
  assert(false && "Return statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundSwitchStatement *statement) {
  assert(false && "Switch statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundClassStatement *statement) {
  assert(false && "Class statement not supported");
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundIndexExpression *statement) {
  assert(false && "Index expression not supported");
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundErrorStatement *statement) {
  assert(false && "Error statement not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundErrorExpression *statement) {
  assert(false && "Error expression not supported");
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundTernaryExpression *statement) {
  assert(false && "Ternary expression not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundNewExpression *statement) {
  assert(false && "New expression not supported");
}

void IRGenerator::visit(
    [[maybe_unused]] binding::BoundAssignmentExpression *statement) {
  assert(false && "Assignment expression not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundExpressionStatement *expression_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Expression Statement", "IR GENERATION");

  expression_statement->getExpression()->accept(this);
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundModuleAccessExpression *statement) {
  assert(false && "Module access expression not supported");
}
void IRGenerator::visit(
    [[maybe_unused]] binding::BoundMemberAccessExpression *statement) {
  assert(false && "Member access expression not supported");
}

void IRGenerator::visit(
    binding::BoundIdentifierExpression *identifier_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Identifier Expression", "IR GENERATION");

  auto symbol = identifier_expression->getSymbol();
  auto llvm_value = m_ir_gen_context.getSymbol(symbol->getName());
  assert(llvm_value && "Symbol not found [BoundIdentifierExpression::visit]");

  const auto &llvm_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(symbol->getType().get());

  llvm::Value *load =
      m_ir_gen_context.getLLVMBuilder()->CreateLoad(llvm_type, llvm_value);
  m_last_value = load;
}

} // namespace ir_gen
} // namespace flow_wing