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




#include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
#include "src/IRGen/IRGenerator/IRGenerator.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"

namespace flow_wing {
namespace ir_gen {
void IRGenerator::emitTypedStore(llvm::Value *target_addr,
                                 types::Type *target_type,
                                 llvm::Value *source_raw_value,
                                 types::Type *source_type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto *llvm_target_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(target_type);

  if (target_type->isDynamic()) {
    if (source_type->isDynamic()) {
      // Dynamic -> Dynamic: Direct struct copy
      llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);
      builder->CreateStore(val_to_store, target_addr);
    } else if (source_type->isPrimitive()) {
      // Primitive -> Dynamic: Box the primitive
      llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);

      llvm::Value *boxed_struct = DynamicValueHandler::storePrimitiveToDynamic(
          val_to_store, val_to_store->getType(), llvm_target_type,
          builder.get(), source_type);

      builder->CreateStore(boxed_struct, target_addr);
    } else {
      // TODO: Future Object/Array Support
      assert(false && "Unsupported type assignment to Dynamic variable");
    }
    return;
  }

  if (source_type->isDynamic()) {
    // Dynamic -> Static Type: Unbox
    auto unboxing_func_name =
        analysis::Builtins::getUnboxingFunctionName(target_type);

    assert(!unboxing_func_name.empty() &&
           "No unboxing function found for this type");

    auto *func =
        m_ir_gen_context.getLLVMModule()->getFunction(unboxing_func_name);
    assert(func && "Unboxing runtime function not found in module");

    auto *unboxed_val = builder->CreateCall(func, {source_raw_value});
    builder->CreateStore(unboxed_val, target_addr);
    return;
  }

  // Primitive->Primitive, Object->Object
  llvm::Value *val_to_store = resolveValue(source_raw_value, source_type);

  if (target_type != source_type) {
    // Handles implicit casts (e.g., int -> float, or Derived* -> Base*)
    val_to_store = convertToTargetType(val_to_store, target_type, source_type);
  }

  builder->CreateStore(val_to_store, target_addr);
}
} // namespace ir_gen
} // namespace flow_wing