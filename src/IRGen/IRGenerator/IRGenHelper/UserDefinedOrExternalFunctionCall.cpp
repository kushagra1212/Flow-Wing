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

#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/utils/LogConfig.h"
namespace flow_wing::ir_gen {

void IRGenerator::dispatchUserDefinedOrExternalFunctionCall(
    binding::BoundCallExpression *call_expression) {
  const auto function_symbol = static_cast<const analysis::FunctionSymbol *>(
      call_expression->getSymbol());
  const std::string &fn_name = function_symbol->getName();

  CODEGEN_DEBUG_LOG("Visiting User-Defined Function: ", fn_name);

  auto llvm_function = m_ir_gen_context.getLLVMModule()->getFunction(fn_name);
  assert(llvm_function &&
         "Function not found [dispatchUserDefinedFunctionCall]");

  auto function_type = static_cast<const types::FunctionType *>(
      function_symbol->getType().get());

  assert(function_type != nullptr &&
         "Function type is null [dispatchUserDefinedFunctionCall]");

  auto &builder = m_ir_gen_context.getLLVMBuilder();
  std::vector<types::Type *> return_types;
  for (const auto &return_type : function_type->getReturnTypes()) {
    return_types.push_back(return_type->type.get());
  }

  std::vector<llvm::Value *> llvm_args = {};
  bool is_void_return = (return_types.size() == 1 &&
                         (*(return_types[0]) ==
                          *(analysis::Builtins::m_nthg_type_instance.get()))) &&
                        !return_types[0]->isDynamic();

  llvm::StructType *return_struct_type = nullptr;
  llvm::Value *return_slot = nullptr;

  if (!is_void_return) {
    return_struct_type =
        m_ir_gen_context.getTypeBuilder()->createOrGetStructType(return_types);
    return_slot = m_ir_gen_context.createAlloca(return_struct_type, "ret_slot");
  }

  bool is_ret_via_arg =
      !is_void_return && function_type->getReturnTypes()[0]->type_convention !=
                             types::TypeConvention::kC;

  if (is_ret_via_arg) {
    llvm_args.push_back(return_slot);
  }

  CODEGEN_DEBUG_LOG("Is return via argument: ", is_ret_via_arg);

  const auto &param_types = function_type->getParameterTypes();
  const auto &arguments = call_expression->getArguments();
  auto default_value_start_index = function_type->getDefaultValueStartIndex();

  for (size_t i = 0; i < arguments.size(); i++) {
    arguments[i]->accept(this);
    assert(m_last_value && "m_last_value is null");

    auto *param_raw_type = param_types[i]->type.get();

    if (param_types[i]->type_convention == types::TypeConvention::kC) {

      llvm::Type *llvm_param_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type);
      llvm::Value *load_value =
          builder->CreateLoad(llvm_param_type, m_last_value, "load_value");
      llvm_args.push_back(load_value);

    } else if (param_types[i]->value_kind == types::ValueKind::kByReference) {
      llvm::Value *ref_arg = nullptr;

      if (param_raw_type->getKind() == types::TypeKind::kArray) {
        if (auto *alloca = llvm::dyn_cast<llvm::AllocaInst>(m_last_value)) {
          if (!alloca->getAllocatedType()->isPointerTy()) {
            ref_arg = m_last_value;
          }
        } else if (llvm::isa<llvm::Argument>(m_last_value)) {
          ref_arg = m_last_value;
        } else if (llvm::isa<llvm::GlobalVariable>(m_last_value)) {
          auto *llvm_type =
              m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type);
          ref_arg = builder->CreateLoad(llvm_type->getPointerTo(), m_last_value,
                                        "global_arr_ptr");
        }
      }

      if (!ref_arg) {
        ref_arg = ensurePointer(m_last_value, m_last_type, "ref_arg");
      }
      llvm_args.push_back(ref_arg);
    } else {
      llvm::Value *arg_slot = nullptr;
      llvm::Value *val = nullptr;

      if (param_raw_type->getKind() == types::TypeKind::kObject) {
        arg_slot =
            m_ir_gen_context.createAlloca(builder->getPtrTy(), "obj_arg_slot");

        if (llvm::isa<llvm::AllocaInst>(m_last_value) ||
            llvm::isa<llvm::GlobalVariable>(m_last_value)) {
          val = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                        ->getLLVMType(param_raw_type)
                                        ->getPointerTo(),
                                    m_last_value, "heap_ptr");
        } else {
          val = m_last_value; // LoadInst/CallInst — already heap ptr
        }
        builder->CreateStore(val, arg_slot);
      } else if (param_raw_type->getKind() == types::TypeKind::kArray) {
        arg_slot = m_ir_gen_context.createAlloca(
            m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type),
            "default_arg_slot");
        emitTypedStore(arg_slot, param_raw_type, m_last_value, m_last_type);
      } else {
        arg_slot = m_ir_gen_context.createAlloca(
            m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type),
            "default_arg_slot");
        val = resolveValue(m_last_value, m_last_type);
        emitTypedStore(arg_slot, param_raw_type, val, m_last_type);
      }
      llvm_args.push_back(arg_slot);
    }

    clearLast();
  }

  for (size_t i = std::max(default_value_start_index, arguments.size());
       i < function_symbol->getParameters().size(); i++) {

    function_symbol->getParameters()[i]->getDefaultValueExpression()->accept(
        this);
    assert(m_last_value && "m_last_value is null for default arg");

    auto *param_raw_type = param_types[i]->type.get();

    if (param_types[i]->value_kind == types::ValueKind::kByReference) {
      llvm::Value *ref_arg = nullptr;

      if (param_raw_type->getKind() == types::TypeKind::kArray) {
        if (auto *alloca = llvm::dyn_cast<llvm::AllocaInst>(m_last_value)) {
          if (!alloca->getAllocatedType()->isPointerTy()) {
            ref_arg = m_last_value;
          }
        } else if (llvm::isa<llvm::Argument>(m_last_value)) {
          ref_arg = m_last_value;
        } else if (llvm::isa<llvm::GlobalVariable>(m_last_value)) {
          auto *llvm_type =
              m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type);
          ref_arg = builder->CreateLoad(llvm_type->getPointerTo(), m_last_value,
                                        "global_arr_ptr");
        }
      }

      if (!ref_arg) {
        ref_arg = ensurePointer(m_last_value, m_last_type, "ref_arg");
      }
      llvm_args.push_back(ref_arg);
    } else {
      llvm::Value *arg_slot = nullptr;
      llvm::Value *val = nullptr;

      if (param_raw_type->getKind() == types::TypeKind::kObject) {
        arg_slot =
            m_ir_gen_context.createAlloca(builder->getPtrTy(), "obj_arg_slot");

        if (llvm::isa<llvm::AllocaInst>(m_last_value) ||
            llvm::isa<llvm::GlobalVariable>(m_last_value)) {
          val = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                        ->getLLVMType(param_raw_type)
                                        ->getPointerTo(),
                                    m_last_value, "heap_ptr");
        } else {
          val = m_last_value; // LoadInst/CallInst — already heap ptr
        }
        builder->CreateStore(val, arg_slot);
      } else if (param_raw_type->getKind() == types::TypeKind::kArray) {
        arg_slot = m_ir_gen_context.createAlloca(
            m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type),
            "default_arg_slot");
        emitTypedStore(arg_slot, param_raw_type, m_last_value, m_last_type);
      } else {
        arg_slot = m_ir_gen_context.createAlloca(
            m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type),
            "default_arg_slot");
        val = resolveValue(m_last_value, m_last_type);
        emitTypedStore(arg_slot, param_raw_type, val, m_last_type);
      }
      llvm_args.push_back(arg_slot);
    }
    clearLast();
  }
  auto call_result = builder->CreateCall(llvm_function, llvm_args);

  if (is_ret_via_arg) {
    if (return_types.size() == 1) {
      auto *ret_type = return_types[0];
      auto *llvm_ret_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(ret_type);

      if (ret_type->getKind() == types::TypeKind::kObject) {
        // Object ret_slot holds a heap pointer — load as ptr
        m_last_value = builder->CreateLoad(llvm_ret_type->getPointerTo(),
                                           return_slot, "ret_load");
      } else {
        // Primitives and arrays: ret_slot is a struct, load from first field
        llvm::Value *field_ptr = builder->CreateStructGEP(
            return_struct_type, return_slot, 0, "ret_field_ptr");
        m_last_value =
            builder->CreateLoad(llvm_ret_type, field_ptr, "ret_load");
      }
      m_last_type = ret_type;

    } else if (return_types.size() > 1) {
      m_last_value = return_slot;
      m_last_llvm_type = return_struct_type;
      m_last_type =
          call_expression->getType().get(); // tuple / multi-return type
    }
  } else {
    m_last_value = call_result;
    m_last_type = call_expression->getType().get();
  }
};
} // namespace flow_wing::ir_gen