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
#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionStatement/BoundFunctionStatement.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/Value.h"
namespace flow_wing::ir_gen {

void IRGenerator::visit(binding::BoundFunctionStatement *function_statement) {

  CODEGEN_DEBUG_LOG("Visiting Bound Function Statement", "IR GENERATION");

  auto function_symbol = static_cast<const analysis::FunctionSymbol *>(
      function_statement->getSymbols().front().get());

  assert(function_symbol && "Function symbol is null");

  auto function_body = function_symbol->getBody().get();

  if (function_body == nullptr) {
    return;
  }

  auto function_type = static_cast<const types::FunctionType *>(
      function_symbol->getType().get());

  auto llvm_function = m_ir_gen_context.getLLVMModule()->getFunction(
      function_symbol->getMangledName());

  assert(llvm_function && "Function not found [BoundFunctionStatement::visit]");

  llvm_function->setLinkage(llvm::Function::WeakODRLinkage);

  auto &builder = m_ir_gen_context.getLLVMBuilder();

  llvm::BasicBlock *saved_block = builder->GetInsertBlock();
  llvm::BasicBlock::iterator saved_point = builder->GetInsertPoint();

  llvm::BasicBlock *entry_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "entry", llvm_function);

  builder->SetInsertPoint(entry_block);

  m_ir_gen_context.pushScope();

  m_ir_gen_context.setSymbol(
      std::string(constants::parameters::kReturn_value_parameter_name),
      llvm_function->arg_begin());

  auto &param_symbols = function_symbol->getParameters();
  size_t param_index =
      (function_type->getReturnTypes().size() > 0 &&
       (*function_type->getReturnTypes()[0]->type.get() ==
        *analysis::Builtins::m_nthg_type_instance.get())) &&
              !function_type->getReturnTypes()[0]->type->isDynamic()
          ? 0
          : 1; // 0 is reserved for return value
  size_t param_symbol_index = 0;
  size_t param_symbols_size = param_symbols.size();

  CODEGEN_DEBUG_LOG("param_symbols_size", param_symbols_size);

  for (; param_symbol_index < param_symbols_size; param_symbol_index++) {
    auto param_symbol = param_symbols[param_symbol_index].get();
    auto param_type =
        function_type->getParameterTypes()[param_symbol_index].get();
    auto param_raw_type = param_type->type.get();
    auto &param_name = param_symbol->getName();
    auto arg_value = llvm_function->arg_begin() + param_index;

    CODEGEN_DEBUG_LOG("param_name", param_name);
    ;
    CODEGEN_DEBUG_LOG("param_raw_type", param_raw_type->getName());

    if (param_type->value_kind == types::ValueKind::kByReference) {
      m_ir_gen_context.setSymbol(param_name, arg_value);
    } else {
      llvm::Type *llvm_param_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type);

      llvm::Value *local_copy = nullptr;
      const llvm::DataLayout &data_layout =
          m_ir_gen_context.getLLVMModule()->getDataLayout();

      if (param_raw_type->getKind() == types::TypeKind::kObject ||
          param_raw_type->getKind() == types::TypeKind::kClass) {
        local_copy = m_ir_gen_context.createAlloca(builder->getPtrTy(),
                                                   param_name + "_local");
        llvm::Align alignment =
            data_layout.getABITypeAlign(builder->getPtrTy());
        uint64_t type_size = data_layout.getTypeAllocSize(builder->getPtrTy());
        builder->CreateMemCpy(local_copy, llvm::MaybeAlign(alignment),
                              arg_value, llvm::MaybeAlign(alignment),
                              type_size);
      } else {
        local_copy = m_ir_gen_context.createAlloca(llvm_param_type,
                                                   param_name + "_local");
        llvm::Align alignment = data_layout.getABITypeAlign(llvm_param_type);
        uint64_t type_size = data_layout.getTypeAllocSize(llvm_param_type);
        builder->CreateMemCpy(local_copy, llvm::MaybeAlign(alignment),
                              arg_value, llvm::MaybeAlign(alignment),
                              type_size);
      }
      m_ir_gen_context.setSymbol(param_name, local_copy);
    }
    param_index++;
  }

  if (function_symbol->getBody()) {
    function_symbol->getBody()->accept(this);
  }

  m_ir_gen_context.popScope();
  if (!builder->GetInsertBlock()->getTerminator()) {
    auto *return_type = llvm_function->getReturnType();
    if (return_type->isVoidTy()) {
      builder->CreateRetVoid();
    } else {
      builder->CreateRet(llvm::Constant::getNullValue(return_type));
    }
  }

  if (saved_block) {
    builder->SetInsertPoint(saved_block, saved_point);
  }
}
}; // namespace flow_wing::ir_gen