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
#include "src/utils/LogConfig.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"

namespace flow_wing::ir_gen {

// `spawn f()` lowers to a single `fw_sched_spawn(&f)`. The call itself is NOT
// emitted here: the runtime performs it later, when the scheduler drains its
// ready-queue after the top-level body finishes.
//
// Only zero-argument callees reach IRGen — the binder rejects arguments,
// because evaluating them at the spawn site means storing the values somewhere
// GC-traced until the deferred call runs, and a queued task has nowhere to put
// them until it owns a stack.
void IRGenerator::visit(binding::BoundSpawnStatement *spawn_statement) {
  CODEGEN_DEBUG_LOG("Visiting Bound Spawn Statement", "IR GENERATION");

  const auto &call_expression = spawn_statement->getCallExpression();
  assert(call_expression && "Spawn statement has no call expression");

  const auto *function_symbol = call_expression->getSymbol();
  assert(function_symbol && "Spawn call expression has no function symbol");

  auto *module = m_ir_gen_context.getLLVMModule();
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto &ctx = *m_ir_gen_context.getLLVMContext();

  llvm::Function *target = module->getFunction(function_symbol->getMangledName());
  assert(target && "Spawn target function not declared in module");

  llvm::Type *void_ty = llvm::Type::getVoidTy(ctx);
  llvm::Type *i8ptr_ty = llvm::Type::getInt8PtrTy(ctx);

  // void fw_sched_spawn(void (*)(void)) — the parameter is declared as a plain
  // i8* here; function and data pointers share a representation on every
  // platform Flow-Wing targets, so this is ABI-compatible with fw_sched.h.
  auto spawn_fn = module->getOrInsertFunction(
      std::string(constants::functions::kSched_spawn_fn),
      llvm::FunctionType::get(void_ty, {i8ptr_ty}, false));

  builder->CreateCall(spawn_fn, {builder->CreateBitCast(target, i8ptr_ty)});
}

} // namespace flow_wing::ir_gen
