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

#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundReturnStatement/BoundReturnStatement.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/Value.h"
namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundReturnStatement *return_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Return Statement", "IR GENERATION");

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto return_ptr = m_ir_gen_context.getSymbol(
      std::string(constants::parameters::kReturn_value_parameter_name));

  const auto &return_expressions = return_statement->getReturnExpressions();
  const auto &function_symbol = return_statement->getFunctionSymbol();

  auto *function_type =
      static_cast<types::FunctionType *>(function_symbol->getType().get());

  if (return_expressions.size() == 1) {
    return_expressions[0]->accept(this);
    auto *target_type = function_type->getReturnTypes()[0]->type.get();

    llvm::Value *val;
    if (target_type->getKind() == types::TypeKind::kObject ||
        target_type->getKind() == types::TypeKind::kArray ||
        target_type->getKind() == types::TypeKind::kClass) {
      val = m_last_value;
    } else {
      val = resolveValue(m_last_value, m_last_type);
    }
    emitTypedStore(return_ptr, target_type, val, m_last_type);
    clearLast();

  } else {
    std::vector<types::Type *> return_types = {};
    std::vector<types::Type *> target_types = {};
    std::vector<llvm::Value *> return_values = {};

    for (size_t i = 0; i < return_expressions.size(); i++) {
      return_expressions[i]->accept(this);
      auto *target_type = function_type->getReturnTypes()[i]->type.get();
      return_types.push_back(m_last_type);
      target_types.push_back(target_type);
      return_values.push_back(m_last_value);
      clearLast();
    }

    llvm::StructType *return_struct_type =
        m_ir_gen_context.getTypeBuilder()->createOrGetStructType(target_types);

    for (size_t i = 0; i < return_values.size(); i++) {

      llvm::Value *val;
      if (target_types[i]->getKind() == types::TypeKind::kObject ||
          target_types[i]->getKind() == types::TypeKind::kArray ||
          target_types[i]->getKind() == types::TypeKind::kClass) {
        val = return_values[i];
      } else {
        val = resolveValue(return_values[i], return_types[i]);
      }

      auto *field_ptr = builder->CreateStructGEP(
          return_struct_type, return_ptr, static_cast<unsigned int>(i),
          "ret_field_" + std::to_string(i));

      emitTypedStore(field_ptr, target_types[i], val, return_types[i]);
    }
  }

  auto *llvm_function = builder->GetInsertBlock()->getParent();
  auto *llvm_return_type = llvm_function->getReturnType();

  if (llvm_return_type->isVoidTy()) {
    builder->CreateRetVoid();
  } else {
    builder->CreateRet(llvm::Constant::getNullValue(llvm_return_type));
  }
  auto *dead_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), // Or builder->getContext()
      "dead_code", llvm_function);
  builder->SetInsertPoint(dead_block);
}
} // namespace flow_wing::ir_gen