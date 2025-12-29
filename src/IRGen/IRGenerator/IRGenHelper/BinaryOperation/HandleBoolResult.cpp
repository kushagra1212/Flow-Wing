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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"

namespace flow_wing::ir_gen {

llvm::Value *IRGenerator::getEqualityComparisonBoolResult(
    llvm::Value *left_value, llvm::Value *right_value, types::Type *left_type,
    types::Type *right_type) {
  if (left_type == analysis::Builtins::m_nirast_type_instance.get() &&
      right_type == analysis::Builtins::m_nirast_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->getTrue();
  }

  if (left_type->getKind() == types::TypeKind::kClass &&
      right_type == analysis::Builtins::m_nirast_type_instance.get()) {
    assert(false && "Unsupported equality comparison");
  }
  if (left_type == analysis::Builtins::m_nirast_type_instance.get() &&
      right_type->getKind() == types::TypeKind::kClass) {
    assert(false && "Unsupported equality comparison");
  }

  if (left_type == analysis::Builtins::m_deci_type_instance.get() ||
      right_type == analysis::Builtins::m_deci_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateFCmpOEQ(
        convertToDouble(left_value, left_value->getType()),
        convertToDouble(right_value, right_value->getType()),
        "equality_comparison_result");
  }

  if (left_type == analysis::Builtins::m_str_type_instance.get() ||
      right_type == analysis::Builtins::m_str_type_instance.get()) {

    auto *string_comparison_function =
        m_ir_gen_context.getLLVMModule()->getFunction(
            flow_wing::ir_gen::constants::functions::kCompare_strings_fn);

    assert(string_comparison_function && "Function  compare_strings not found");

    return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
        m_ir_gen_context.getLLVMBuilder()->CreateCall(
            string_comparison_function,
            {convertToString(left_value, left_value->getType()),
             convertToString(right_value, right_value->getType())}),
        m_ir_gen_context.getLLVMBuilder()->getInt32(0),
        "equality_comparison_result");
  }

  if (left_type == analysis::Builtins::m_int64_type_instance.get() ||
      right_type == analysis::Builtins::m_int64_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
        convertToInt64(left_value, left_value->getType()),
        convertToInt64(right_value, right_value->getType()),
        "equality_comparison_result");
  }

  if (left_type == analysis::Builtins::m_int32_type_instance.get() ||
      right_type == analysis::Builtins::m_int32_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
        convertToInt32(left_value, left_value->getType()),
        convertToInt32(right_value, right_value->getType()),
        "equality_comparison_result");
  }

  return m_ir_gen_context.getLLVMBuilder()->CreateICmpEQ(
      left_value, right_value, "equality_comparison_result");
}

llvm::Value *IRGenerator::getInequalityComparisonBoolResult(
    llvm::Value *left_value, llvm::Value *right_value, types::Type *left_type,
    types::Type *right_type) {
  return m_ir_gen_context.getLLVMBuilder()->CreateNot(
      getEqualityComparisonBoolResult(left_value, right_value, left_type,
                                      right_type));
}

llvm::Value *
IRGenerator::getLogicalAndBoolResult(llvm::Value *left_value,
                                     llvm::Value *right_value,
                                     [[maybe_unused]] types::Type *left_type,
                                     [[maybe_unused]] types::Type *right_type) {
  return m_ir_gen_context.getLLVMBuilder()->CreateLogicalAnd(
      left_value, right_value, "logical_and_result");
}

llvm::Value *
IRGenerator::getLogicalOrBoolResult(llvm::Value *left_value,
                                    llvm::Value *right_value,
                                    [[maybe_unused]] types::Type *left_type,
                                    [[maybe_unused]] types::Type *right_type) {
  return m_ir_gen_context.getLLVMBuilder()->CreateLogicalOr(
      left_value, right_value, "logical_or_result");
}

llvm::Value *
IRGenerator::getLessThanBoolResult(llvm::Value *left_value,
                                   llvm::Value *right_value,
                                   [[maybe_unused]] types::Type *left_type,
                                   [[maybe_unused]] types::Type *right_type) {

  if (left_type == analysis::Builtins::m_deci_type_instance.get() ||
      right_type == analysis::Builtins::m_deci_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateFCmpOLT(
        convertToDouble(left_value, left_value->getType()),
        convertToDouble(right_value, right_value->getType()),
        "less_than_result");
  }

  if (left_type == analysis::Builtins::m_str_type_instance.get() ||
      right_type == analysis::Builtins::m_str_type_instance.get()) {

    auto *string_comparison_function =
        m_ir_gen_context.getLLVMModule()->getFunction(
            flow_wing::ir_gen::constants::functions::kCompare_strings_fn);

    assert(string_comparison_function &&
           "Function  less_than_strings not found");

    return m_ir_gen_context.getLLVMBuilder()->CreateICmpSLT(
        m_ir_gen_context.getLLVMBuilder()->CreateCall(
            string_comparison_function,
            {convertToString(left_value, left_value->getType()),
             convertToString(right_value, right_value->getType())}),
        m_ir_gen_context.getLLVMBuilder()->getInt32(0), "less_than_result");
  }

  if (left_type == analysis::Builtins::m_int64_type_instance.get() ||
      right_type == analysis::Builtins::m_int64_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateICmpSLT(
        convertToInt64(left_value, left_value->getType()),
        convertToInt64(right_value, right_value->getType()),
        "less_than_result");
  }

  if (left_type == analysis::Builtins::m_int32_type_instance.get() ||
      right_type == analysis::Builtins::m_int32_type_instance.get()) {
    return m_ir_gen_context.getLLVMBuilder()->CreateICmpSLT(
        convertToInt32(left_value, left_value->getType()),
        convertToInt32(right_value, right_value->getType()),
        "less_than_result");
  }

  return m_ir_gen_context.getLLVMBuilder()->CreateICmpSLT(
      left_value, right_value, "less_than_result");
}

llvm::Value *IRGenerator::getLessThanOrEqualBoolResult(
    llvm::Value *left_value, llvm::Value *right_value, types::Type *left_type,
    types::Type *right_type) {

  // Logic: A <= B is equivalent to NOT(A > B)
  return m_ir_gen_context.getLLVMBuilder()->CreateNot(
      getGreaterThanBoolResult(left_value, right_value, left_type, right_type),
      "lte_res");
}

llvm::Value *IRGenerator::getGreaterThanBoolResult(llvm::Value *left_value,
                                                   llvm::Value *right_value,
                                                   types::Type *left_type,
                                                   types::Type *right_type) {
  // LOGIC: A > B is equivalent to B < A
  return getLessThanBoolResult(right_value, left_value, right_type, left_type);
}

llvm::Value *IRGenerator::getGreaterThanOrEqualBoolResult(
    llvm::Value *left_value, llvm::Value *right_value, types::Type *left_type,
    types::Type *right_type) {

  // Logic: A >= B is equivalent to NOT(A < B)
  return m_ir_gen_context.getLLVMBuilder()->CreateNot(
      getLessThanBoolResult(left_value, right_value, left_type, right_type),
      "gte_res");
}

llvm::Value *IRGenerator::getBooleanResult(llvm::Value *left_value,
                                           llvm::Value *right_value,
                                           lexer::TokenKind operator_kind,
                                           types::Type *left_type,
                                           types::Type *right_type) {

  switch (operator_kind) {
  case lexer::TokenKind::kEqualsEqualsToken:
    return getEqualityComparisonBoolResult(left_value, right_value, left_type,
                                           right_type);
  case lexer::TokenKind::kBangEqualsToken:
    return getInequalityComparisonBoolResult(left_value, right_value, left_type,
                                             right_type);
  case lexer::TokenKind::kAmpersandAmpersandToken:
    return getLogicalAndBoolResult(left_value, right_value, left_type,
                                   right_type);
  case lexer::TokenKind::kPipePipeToken:
    return getLogicalOrBoolResult(left_value, right_value, left_type,
                                  right_type);
  case lexer::TokenKind::kLessToken:
    return getLessThanBoolResult(left_value, right_value, left_type,
                                 right_type);
  case lexer::TokenKind::kLessOrEqualsToken:
    return getLessThanOrEqualBoolResult(left_value, right_value, left_type,
                                        right_type);
  case lexer::TokenKind::kGreaterToken:
    return getGreaterThanBoolResult(left_value, right_value, left_type,
                                    right_type);
  case lexer::TokenKind::kGreaterOrEqualsToken:
    return getGreaterThanOrEqualBoolResult(left_value, right_value, left_type,
                                           right_type);
  default:
    assert(false && "Unsupported boolean operator");
    return nullptr;
  }
}
} // namespace flow_wing::ir_gen