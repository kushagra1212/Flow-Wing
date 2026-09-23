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
#include "src/SemanticAnalyzer/BoundStatements/BoundSpawnStatement/BoundSpawnStatement.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"

namespace flow_wing::ir_gen {

// `spawn f(...)` does NOT emit the call. It records everything needed to make
// the call later, and hands that to the scheduler.
//
// With no arguments that is just a function pointer:
//     fw_sched_spawn(&f)
//
// With arguments there is a problem to solve. Go-style semantics say the
// arguments are evaluated at the SPAWN SITE, but the task does not run until
// the drain — and a queued task owns no stack yet, because stacks are taken on
// first resume. So the values need a home in between.
//
// That home is a GC object built per spawn site:
//
//     %fw_spawn_args.N = type { <param 0 type>, <param 1 type>, ... }
//
// getOrEmitPlain() gives it a descriptor listing its pointer fields, so the GC
// traces any strings or objects inside it. fw_sched_spawn_args roots the whole
// block for the task's life.
//
// A generated thunk performs the real call:
//
//     void __fw_spawn_thunk.N(ptr %args) {
//       call @f(ptr gep(%args, 0), ptr gep(%args, 1))
//     }
//
// Passing GEPs straight into the argument object works because every FlowWing
// parameter is passed BY POINTER — even an int is `ptr` in the callee's
// signature — and the object outlives the call.
void IRGenerator::visit(binding::BoundSpawnStatement *spawn_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Spawn Statement", "IR GENERATION");

  const auto &call_expression = spawn_statement->getCallExpression();
  assert(call_expression && "Spawn statement has no call expression");

  const auto *function_symbol = call_expression->getSymbol();
  assert(function_symbol && "Spawn call expression has no function symbol");

  auto *module = m_ir_gen_context.getLLVMModule();
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto &ctx = *m_ir_gen_context.getLLVMContext();

  // `spawn f(...)` where `f` is a function value (a variable, a field, a
  // parameter of a function type) runs whatever function `f` holds at the
  // spawn site. That is known only when the program runs, so the address is
  // evaluated here and travels with the task.
  const bool is_function_value = function_symbol->isParameterSymbol();

  llvm::Function *target = nullptr;
  llvm::Value *target_value = nullptr;
  if (is_function_value) {
    target_value = emitIndirectCallee(call_expression.get());
  } else {
    target = module->getFunction(function_symbol->getMangledName());

    // The binder rejects everything that has no emitted function — built-ins,
    // methods, unresolved names. If one still reaches here, stop with a
    // message instead of dereferencing null: asserts are compiled out in
    // Release, and this used to surface as a bare segfault with no indication
    // of the cause.
    if (target == nullptr) {
      assert(target && "Spawn target function not declared in module");
      llvm::report_fatal_error(
          llvm::Twine("spawn target '") + function_symbol->getMangledName() +
          "' has no function in the module; the binder should have rejected it");
    }
    target_value = target;
  }

  llvm::Type *void_ty = llvm::Type::getVoidTy(ctx);
  llvm::Type *i8ptr_ty = llvm::Type::getInt8PtrTy(ctx);

  const auto &arguments = call_expression->getArguments();

  // ---- no arguments: hand the function pointer over directly ---------------
  if (arguments.empty()) {
    auto spawn_fn = module->getOrInsertFunction(
        std::string(constants::functions::kSched_spawn_fn),
        llvm::FunctionType::get(void_ty, {i8ptr_ty}, false));

    builder->CreateCall(spawn_fn,
                        {builder->CreateBitCast(target_value, i8ptr_ty)});
    return;
  }

  // ---- with arguments: build the argument object ---------------------------
  auto *function_type =
      static_cast<const types::FunctionType *>(function_symbol->getType().get());
  const auto &param_types = function_type->getParameterTypes();

  // Same reasoning: a variadic built-in declares fewer parameters than the call
  // passes, and indexing param_types by argument position then walks off the
  // end. The binder rejects those, so this is a backstop, not a policy.
  if (param_types.size() < arguments.size()) {
    assert(false && "more spawn arguments than the callee declares");
    llvm::report_fatal_error(
        llvm::Twine("spawn call to '") + function_symbol->getMangledName() +
        "' passes more arguments than the callee declares");
  }

  // One struct type per spawn site. The counter keeps names unique inside the
  // module; two sites calling the same function still get separate types,
  // which costs nothing and keeps the mapping obvious in the IR.
  const unsigned site_id = m_spawn_site_counter++;

  // The field type must match what the callee's parameter slot would be, and
  // that is NOT always getLLVMType(param). An object/class parameter is passed
  // as a POINTER to the instance, so its slot is a bare pointer — storing the
  // whole struct type there would both waste space and give getOrEmitPlain the
  // wrong pointer offsets.
  auto isReferenceKind = [](const types::Type *t) {
    return t->getKind() == types::TypeKind::kObject ||
           t->getKind() == types::TypeKind::kClass ||
           t->getKind() == types::TypeKind::kFunction;
  };

  std::vector<llvm::Type *> field_types;
  field_types.reserve(arguments.size());
  for (size_t i = 0; i < arguments.size(); i++) {
    auto *param_raw_type = param_types[i]->type.get();
    field_types.push_back(
        isReferenceKind(param_raw_type)
            ? static_cast<llvm::Type *>(builder->getPtrTy())
            : m_ir_gen_context.getTypeBuilder()->getLLVMType(param_raw_type));
  }

  // A function value's address rides in one more field, after the arguments.
  const unsigned target_field = static_cast<unsigned>(arguments.size());
  if (is_function_value) {
    field_types.push_back(builder->getPtrTy());
  }

  auto *args_struct_ty = llvm::StructType::create(
      ctx, field_types, "fw_spawn_args." + std::to_string(site_id));

  llvm::Constant *descriptor =
      m_ir_gen_context.getGCDescriptorEmitter()->getOrEmitPlain(args_struct_ty);

  const llvm::DataLayout &data_layout = module->getDataLayout();
  const uint64_t args_size = data_layout.getTypeAllocSize(args_struct_ty);

  // GC memory, not an alloca: it has to outlive this stack frame.
  llvm::Value *args_raw =
      m_ir_gen_context.createGcAlloc(args_size, descriptor, "spawn_args");

  // Root the block while the remaining arguments are evaluated: each of those
  // can allocate, and under FW_GC_STRESS every allocation collects.
  llvm::AllocaInst *args_root =
      m_ir_gen_context.createAlloca(i8ptr_ty, "spawn_args_root");
  builder->CreateStore(args_raw, args_root);
  m_ir_gen_context.addGcRootAlloca(args_root);

  // A function is not a GC object; the collector passes over this field.
  if (is_function_value) {
    builder->CreateStore(target_value,
                         builder->CreateStructGEP(args_struct_ty, args_raw,
                                                  target_field,
                                                  "spawn_target_slot"));
  }

  for (size_t i = 0; i < arguments.size(); i++) {
    arguments[i]->accept(this);
    assert(m_last_value && "spawn argument produced no value");

    auto *param_raw_type = param_types[i]->type.get();

    // Re-load through the root: an argument evaluated earlier may have moved
    // nothing, but the pointer must come from the rooted slot so a collection
    // during evaluation cannot leave a stale copy behind.
    llvm::Value *args_ptr =
        builder->CreateLoad(i8ptr_ty, args_root, "spawn_args_live");

    llvm::Value *field = builder->CreateStructGEP(
        args_struct_ty, args_ptr, static_cast<unsigned>(i), "spawn_arg_slot");

    // Mirror the three cases the normal call path uses. Using the last one for
    // everything is what made an array argument read uninitialised memory:
    // resolveValue() is wrong for an aggregate.
    if (isReferenceKind(param_raw_type)) {
      // Reference kinds store the instance POINTER, so the task sees the same
      // object the caller has — mutations either side are visible to both.
      llvm::Value *val = m_last_value;
      if (llvm::isa<llvm::AllocaInst>(m_last_value) ||
          llvm::isa<llvm::GlobalVariable>(m_last_value) ||
          llvm::isa<llvm::GetElementPtrInst>(m_last_value) ||
          llvm::isa<llvm::GEPOperator>(m_last_value)) {
        // The value is the ADDRESS of a slot holding the pointer, not the
        // pointer itself; load through it.
        val = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                      ->getLLVMType(param_raw_type)
                                      ->getPointerTo(),
                                  m_last_value, "heap_ptr");
      }
      builder->CreateStore(val, field);

    } else if (param_raw_type->getKind() == types::TypeKind::kArray) {
      // Arrays are copied element by element into the block, so the task gets
      // a snapshot taken at the spawn site.
      emitTypedStore(field, param_raw_type, m_last_value, m_last_type);

    } else {
      llvm::Value *value = resolveValue(m_last_value, m_last_type);
      emitTypedStore(field, param_raw_type, value, m_last_type);
    }
  }

  // ---- the thunk ----------------------------------------------------------
  const std::string thunk_name = "__fw_spawn_thunk." + std::to_string(site_id);

  llvm::Function *thunk = llvm::Function::Create(
      llvm::FunctionType::get(void_ty, {i8ptr_ty}, false),
      llvm::Function::InternalLinkage, thunk_name, module);

  {
    llvm::BasicBlock *saved_block = builder->GetInsertBlock();
    llvm::BasicBlock::iterator saved_point = builder->GetInsertPoint();

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(ctx, "entry", thunk);
    builder->SetInsertPoint(entry);

    llvm::Value *thunk_args = &*thunk->arg_begin();

    // Every FlowWing parameter is passed by pointer, so the callee receives
    // addresses INSIDE the argument object. That is safe: the scheduler keeps
    // the object rooted until the task finishes.
    std::vector<llvm::Value *> call_args;
    call_args.reserve(arguments.size());
    for (size_t i = 0; i < arguments.size(); i++) {
      call_args.push_back(builder->CreateStructGEP(
          args_struct_ty, thunk_args, static_cast<unsigned>(i), "arg"));
    }

    if (is_function_value) {
      llvm::Value *fn = builder->CreateLoad(
          builder->getPtrTy(),
          builder->CreateStructGEP(args_struct_ty, thunk_args, target_field,
                                   "target_slot"),
          "target");
      builder->CreateCall(
          m_ir_gen_context.getTypeBuilder()->convertFunction(function_type), fn,
          call_args);
    } else {
      builder->CreateCall(target->getFunctionType(), target, call_args);
    }
    builder->CreateRetVoid();

    builder->SetInsertPoint(saved_block, saved_point);
  }

  // ---- queue it -----------------------------------------------------------
  auto spawn_args_fn = module->getOrInsertFunction(
      std::string(constants::functions::kSched_spawn_args_fn),
      llvm::FunctionType::get(void_ty, {i8ptr_ty, i8ptr_ty}, false));

  llvm::Value *args_final =
      builder->CreateLoad(i8ptr_ty, args_root, "spawn_args_final");

  builder->CreateCall(spawn_args_fn,
                      {builder->CreateBitCast(thunk, i8ptr_ty), args_final});
}

} // namespace flow_wing::ir_gen
