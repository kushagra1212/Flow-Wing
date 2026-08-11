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

#include "src/IRGen/GlobalDeclarationsInitializer/GlobalDeclarationsInitializer.hpp"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ParameterSymbol.hpp"
#include "src/utils/LogConfig.h"
#include <algorithm>
#include <cassert>
namespace flow_wing::ir_gen {

void IRGenerator::dispatchUserDefinedOrExternalFunctionCall(
    binding::BoundCallExpression *call_expression) {


     const  analysis::FunctionSymbol *  function_symbol =static_cast<const analysis::FunctionSymbol *>(
    call_expression->getSymbol());
    
  const std::string &fn_name = function_symbol->getMangledName();

  CODEGEN_DEBUG_LOG("Visiting User-Defined Function: ", fn_name);

  if (call_expression->getUseVirtualDispatch()) {
    const auto &args = call_expression->getArguments();
    assert(!args.empty() && call_expression->getImplicitReceiverLast());
    types::Type *recv_ty = args.back()->getType().get();
    assert(recv_ty->getKind() == types::TypeKind::kClass &&
           "virtual dispatch receiver must be a class");
    GlobalDeclarationsInitializer decl_helper(m_ir_gen_context);
    decl_helper.ensureImportedClassExterns(
        static_cast<types::ClassType *>(recv_ty));
  }

  CODEGEN_DEBUG_LOG("fn_name", fn_name);
 
  llvm::Value *callee_val = nullptr;
  llvm::Function *llvm_function = nullptr;
  const bool is_indirect_call = function_symbol->isParameterSymbol();

  auto &builder = m_ir_gen_context.getLLVMBuilder();

  if(!is_indirect_call) {
    llvm_function = m_ir_gen_context.getLLVMModule()->getFunction(fn_name);
    assert(llvm_function && "Function not found [dispatchUserDefinedFunctionCall]");
    callee_val = llvm_function;
  }else{
    llvm::Value *fn_ptr_storage = m_ir_gen_context.getSymbol(function_symbol->getName());
    assert(fn_ptr_storage && "Function pointer symbol not found in local context");
    
    callee_val = builder->CreateLoad(
        builder->getPtrTy(), fn_ptr_storage, "fn_ptr_load");
  }


  auto function_type = static_cast<const types::FunctionType *>(
      function_symbol->getType().get());

  assert(function_type != nullptr &&
         "Function type is null [dispatchUserDefinedFunctionCall]");

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
  const auto default_value_start_index =
      function_type->getDefaultValueStartIndex();
  const size_t num_params = param_types.size();


  CODEGEN_DEBUG_LOG("num_params", num_params);

  if(!is_indirect_call) {

    assert(num_params == function_symbol->getParameters().size() &&
           "param_types and FunctionSymbol parameters must match");
  }




  const bool last_arg_is_implicit_receiver =
      call_expression->getImplicitReceiverLast();

  const size_t n_explicit =
      last_arg_is_implicit_receiver ? arguments.size() - 1 : arguments.size();
  const size_t param_limit_excl_receiver =
      last_arg_is_implicit_receiver ? num_params - 1 : num_params;

  auto emitOneParameter = [&](binding::BoundExpression *bound_expr,
                              size_t param_idx) {
    bound_expr->accept(this);
    assert(m_last_value && "m_last_value is null");

    auto *param_raw_type = param_types[param_idx]->type.get();

    if (param_types[param_idx]->type_convention == types::TypeConvention::kC) {

      llvm::Type *llvm_param_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type);
      llvm::Value *load_value =
          builder->CreateLoad(llvm_param_type, m_last_value, "load_value");
      llvm_args.push_back(load_value);

    } else if (param_types[param_idx]->value_kind ==
               types::ValueKind::kByReference) {
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

      if (param_raw_type->getKind() == types::TypeKind::kObject ||
          param_raw_type->getKind() == types::TypeKind::kClass ||
          param_raw_type->getKind() == types::TypeKind::kFunction) {
        arg_slot =
            m_ir_gen_context.createAlloca(builder->getPtrTy(), "obj_arg_slot");

        bool is_inline_array_object = false;
        if (auto *gep = llvm::dyn_cast<llvm::GEPOperator>(m_last_value)) {
          if (gep->getSourceElementType()->isArrayTy() &&
              m_last_type->getKind() == types::TypeKind::kObject) {
            is_inline_array_object = true;
          }
        }

        // A boxed dynamic argument (a container element, e.g.
        // `takes(outer.get(0))`) is `{ i32 tag; i64 value }`; this slot holds a
        // bare pointer, so the payload has to be unboxed first — otherwise the
        // tag word is passed as the instance address.
        const bool is_boxed_dynamic_arg =
            m_last_type != nullptr && m_last_type->isDynamic() &&
            param_raw_type->getKind() != types::TypeKind::kFunction;

        if (is_boxed_dynamic_arg) {
          val = unboxDynamicToReference(m_last_value, m_last_type,
                                        param_raw_type->getName());
        } else if ((llvm::isa<llvm::AllocaInst>(m_last_value) ||
             llvm::isa<llvm::GlobalVariable>(m_last_value) ||
             llvm::isa<llvm::GetElementPtrInst>(m_last_value) ||
             llvm::isa<llvm::GEPOperator>(m_last_value)) &&
            !is_inline_array_object) {
          // Member field holding a class reference: m_last_value is the field
          // address (e.g. GEP to `c` in `self.c.bump()`), not the heap pointer.
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
      // Temp-safety: if this argument slot holds a GC heap pointer, root it so
      // an already-evaluated argument survives the allocations performed while
      // evaluating later arguments (and inside the callee's prologue). Two
      // shapes qualify: a pointer-typed slot of a reference type (object / class
      // / array / string), and a boxed-dynamic slot (`%fg_dyn_type`) whose i64
      // payload may hold a GC string/object/array pointer. The shadow-frame
      // emitter registers the dynamic box's payload field as the actual root and
      // fw_gc_resolve_object skips non-pointer payloads, so rooting the box is
      // safe. Without this, a chained call like `v.push("a").push("b")` — which
      // materializes every argument (each a fw_gc_alloc'd string) before making
      // any call — frees the earlier arguments while boxing the later ones.
      if (auto *slot = llvm::dyn_cast<llvm::AllocaInst>(arg_slot)) {
        const bool is_gc_ref = param_raw_type->isGcReference();
        const bool is_boxed_dynamic =
            param_raw_type->isDynamic() &&
            slot->getAllocatedType()->isStructTy();
        if ((is_gc_ref && slot->getAllocatedType()->isPointerTy()) ||
            is_boxed_dynamic)
          m_ir_gen_context.addGcRootAlloca(slot);
      }
      llvm_args.push_back(arg_slot);
    }

    clearLast();
  };

  // Explicit arguments (call-site), excluding trailing implicit receiver
  for (size_t i = 0; i < n_explicit && i < param_limit_excl_receiver; i++) {
    emitOneParameter(arguments[i].get(), i);
  }

  //  Default parameters not supplied at the call site (globals + members)
  if (default_value_start_index != static_cast<size_t>(-1)) {
    for (size_t i = std::max(default_value_start_index, n_explicit);
         i < param_limit_excl_receiver; i++) {
      const auto &def_ptr =
          function_symbol->getParameters()[i]->getDefaultValueExpression();
      assert(def_ptr &&
             "missing bound default for defaulted parameter index");
      emitOneParameter(def_ptr.get(), i);
    }
  }

  // Implicit class receiver last (instance methods / super)
  if (last_arg_is_implicit_receiver) {
    emitOneParameter(arguments.back().get(), num_params - 1);
  }


  llvm::FunctionType *callee_ft = nullptr;
  if (llvm_function) {
    callee_ft = llvm_function->getFunctionType();
  } else {
    std::vector<llvm::Type*> arg_llvm_types;
    for (auto *arg : llvm_args) {
      arg_llvm_types.push_back(arg->getType());
    }
    
    llvm::Type *ret_llvm_type = builder->getVoidTy();
    if (!is_void_return && !is_ret_via_arg) {
      if (return_types.size() == 1) {
        ret_llvm_type = m_ir_gen_context.getTypeBuilder()->getLLVMType(return_types[0]);
      } else {
        ret_llvm_type = return_struct_type;
      }
    }
    callee_ft = llvm::FunctionType::get(ret_llvm_type, arg_llvm_types, false);
  }


  llvm::CallInst *call_result = nullptr;
  if (call_expression->getUseVirtualDispatch()) {
    const llvm::DataLayout &dl =
        m_ir_gen_context.getLLVMModule()->getDataLayout();
    const uint64_t ptr_size = dl.getPointerSize();

    llvm::Value *self_slot = llvm_args.back();
    types::Type *recv_ty = param_types.back()->type.get();
    assert(recv_ty->getKind() == types::TypeKind::kClass &&
           "virtual dispatch requires class receiver");
    llvm::Type *struct_llvm =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(recv_ty);
    auto *st = llvm::cast<llvm::StructType>(struct_llvm);
    llvm::Value *heap_ptr = builder->CreateLoad(
        builder->getPtrTy(), self_slot, "virt.self_heap");
    llvm::Value *this_struct = builder->CreateBitCast(
        heap_ptr, struct_llvm->getPointerTo(), "virt.this");
    llvm::Value *vptr_ptr =
        builder->CreateStructGEP(st, this_struct, 0, "virt.vptr_slot");
    llvm::Value *vtable_i8 =
        builder->CreateLoad(builder->getPtrTy(), vptr_ptr, "virt.vtbl");
    llvm::Type *i8_ty = llvm::Type::getInt8Ty(
        m_ir_gen_context.getLLVMModule()->getContext());
    llvm::Value *fn_ptr_i8 = builder->CreateInBoundsGEP(
        i8_ty, vtable_i8,
        llvm::ConstantInt::get(
            llvm::Type::getInt64Ty(
                m_ir_gen_context.getLLVMModule()->getContext()),
            call_expression->getVirtualSlot() * ptr_size),
        "virt.method_slot");
    llvm::Value *fn_ptr_raw =
        builder->CreateLoad(builder->getPtrTy(), fn_ptr_i8, "virt.fn_ptr");
        llvm::Value *callee_val_virt = builder->CreateBitCast(fn_ptr_raw, builder->getPtrTy());
        call_result = builder->CreateCall(callee_ft, callee_val_virt, llvm_args);
  } else {
    call_result = builder->CreateCall(callee_ft, callee_val, llvm_args);
  }

  // Indirect calls (vtable dispatch) do not inherit the callee Function's
  // parameter attributes. Copy the full AttributeList so SysV x86-64 `sret`
  // on the hidden return slot matches the declaration (direct calls get the
  // same treatment for consistency).
  if (llvm_function) {
    call_result->setAttributes(llvm_function->getAttributes());
  }


  if (is_ret_via_arg) {
    if (return_types.size() == 1) {
      auto *ret_type = return_types[0];
      auto *llvm_ret_type =
          m_ir_gen_context.getTypeBuilder()->getLLVMType(ret_type);

      // Temp-safety: when the callee returns a GC reference (object / class /
      // array / string) through `return_slot`, that heap pointer now lives only
      // in the slot. Root the slot's pointer leaf (offset 0) so the returned
      // value survives caller-side `fw_gc_alloc` safepoints — e.g. copying it
      // into a destination variable (`var f = fetch()`) allocates first, which
      // would otherwise collect the just-returned array/object. The shadow frame
      // reads `*slot` each collection; non-pointer/uninitialized reads are
      // skipped by fw_gc_resolve_object.
      const bool ret_is_gc_ref = ret_type->isGcReference();
      if (auto *rs = llvm::dyn_cast<llvm::AllocaInst>(return_slot)) {
        if (ret_is_gc_ref) {
          // Root EVERY heap-pointer leaf of the return slot. A class/string
          // return is a single pointer at offset 0, but an array return is
          // stored INLINE (e.g. `Obj[3]` → three string pointers at offsets 0,
          // 8, 16), so rooting only offset 0 would leave later elements' strings
          // to be collected. rootMultiReturnSlotLeaves walks the layout.
          rootMultiReturnSlotLeaves(rs, return_struct_type);
        } else if (ret_type->isDynamic()) {
          // A dynamic return is a boxed `{ i32 tag; i64 value }`; the value at
          // offset 8 may hold a GC string/object/array pointer (e.g. a function
          // whose inferred return is a concatenated string). Root that payload
          // slot so it survives caller-side safepoints (the dynamic→target
          // conversion allocates); fw_gc_resolve_object skips non-pointer tags.
          m_ir_gen_context.addGcRootSlot(rs, 8);
        }
      }

      if (ret_type->getKind() == types::TypeKind::kObject ||
          ret_type->getKind() == types::TypeKind::kClass) {
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