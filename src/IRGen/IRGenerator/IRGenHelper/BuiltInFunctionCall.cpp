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
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/utils/LogConfig.h"
#include <string>
 #include "src/IRGen/IRGenerator/IRGenHelper/DynamicValueHandler.h"
namespace flow_wing::ir_gen {

void IRGenerator::emitRecursivePrint(llvm::Value *value, types::Type *type,
                                     bool is_nested) {
  auto *mod = m_ir_gen_context.getLLVMModule();
  const std::unique_ptr<llvm::IRBuilder<>> &builder =
      m_ir_gen_context.getLLVMBuilder();
  auto *printf_fn =
      mod->getFunction(std::string(constants::functions::kPrintf_fn));

  // 1. Handle Dynamic Types
  if (type->isDynamic()) {
    auto *print_dyn_fn =
        mod->getFunction(std::string(constants::functions::kPrint_dynamic_fn));
    assert(print_dyn_fn && "kPrint_dynamic_fn not found");

    llvm::Value *dyn_ptr = ensurePointer(value, type, "print_dyn_tmp");
    builder->CreateCall(print_dyn_fn, {dyn_ptr});
    return;
  }

  if (type->getKind() == types::TypeKind::kObject) {

    CODEGEN_DEBUG_LOG("Printing Object", type->getName());
    auto *custom_type = static_cast<types::CustomObjectType *>(type);

    llvm::Value *obj_ptr = ensurePointer(value, type, "print_tmp");

    llvm::Function *printer = getOrCreateObjectPrinter(custom_type);
    llvm::Value *void_ptr =
        builder->CreateBitCast(obj_ptr, builder->getInt8PtrTy());

    builder->CreateCall(printer, {void_ptr});
    return;
  }

  if (type->getKind() == types::TypeKind::kArray) {
    CODEGEN_DEBUG_LOG("Printing Array", type->getName());
    auto *array_type = static_cast<types::ArrayType *>(type);

    llvm::Value *arr_ptr = ensurePointer(value, type, "array_print_tmp");

    llvm::Function *printer = getOrCreateArrayPrinter(array_type);
    llvm::Value *void_ptr =
        builder->CreateBitCast(arr_ptr, builder->getInt8PtrTy());
    builder->CreateCall(printer, {void_ptr});
    return;
  }

  // 3. Handle Primitives (String/Char/Numbers)
  bool is_string = (*type == *analysis::Builtins::m_str_type_instance.get());
  bool is_char = (*type == *analysis::Builtins::m_char_type_instance.get());

  // Opening quotes for nested types
  if (is_nested) {
    if (is_string)
      builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("\"")});
    if (is_char)
      builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("'")});
  }

  llvm::Value *stringified_value =
      convertToString(value, value->getType(), is_char);
  builder->CreateCall(printf_fn, {stringified_value});

  // Closing quotes for nested types
  if (is_nested) {
    if (is_string)
      builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("\"")});
    if (is_char)
      builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("'")});
  }
}

llvm::Function *IRGenerator::getOrCreateArrayPrinter(types::ArrayType *type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto mod = m_ir_gen_context.getLLVMModule();

  std::string name = type->getName();
  std::replace(name.begin(), name.end(), '[', '_');
  std::replace(name.begin(), name.end(), ']', '_');
  std::string func_name = "fg_print_array_" + name;

  if (auto existing_fn = mod->getFunction(func_name)) {
    return existing_fn;
  }

  llvm::FunctionType *fn_type = llvm::FunctionType::get(
      builder->getVoidTy(), {builder->getInt8PtrTy()}, false);

  // Per-TU private printers: LinkOnceODR merges duplicate globals across .obj
  // files on ELF, but MSVC (LNK1227) rejects conflicting COMDAT "weak default"
  // selections when the same `fg_print_*` is emitted from multiple TUs (e.g.
  // brought `file1.fg` + main `task2.fg`). Internal linkage is correct because
  // each object file only calls its own copy.
  llvm::Function *printer_fn = llvm::Function::Create(
      fn_type, llvm::Function::InternalLinkage, func_name, mod);

  auto prev_block = builder->GetInsertBlock();
  auto prev_insert_point = builder->GetInsertPoint();

  llvm::BasicBlock *entry_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "entry", printer_fn);
  builder->SetInsertPoint(entry_block);

  auto printf_fn = mod->getOrInsertFunction(
      std::string(constants::functions::kPrintf_fn),
      llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt8PtrTy()},
                              true));

  // Cast i8* back to [N x T]*
  llvm::Type *llvm_array_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
  llvm::Value *void_ptr = printer_fn->getArg(0);
  llvm::Value *array_ptr = builder->CreateBitCast(
      void_ptr, llvm_array_type->getPointerTo(), "typed_array_ptr");

  builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("[ ")});

  const auto &dims = type->getDimensions();
  uint64_t outer_dim = dims[0];

  // Handle empty array edge case
  if (outer_dim == 0) {
    builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("]")});
    builder->CreateRetVoid();
    if (prev_block)
      builder->SetInsertPoint(prev_block, prev_insert_point);
    return printer_fn;
  }

  // --- Loop Blocks ---
  llvm::BasicBlock *loop_cond = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "loop.cond", printer_fn);
  llvm::BasicBlock *loop_body = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "loop.body", printer_fn);
  llvm::BasicBlock *loop_exit = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "loop.exit", printer_fn);

  builder->CreateBr(loop_cond);

  // --- Loop Condition ---
  builder->SetInsertPoint(loop_cond);
  llvm::PHINode *idx_phi = builder->CreatePHI(builder->getInt64Ty(), 2, "i");
  idx_phi->addIncoming(builder->getInt64(0), entry_block);

  llvm::Value *cmp =
      builder->CreateICmpULT(idx_phi, builder->getInt64(outer_dim));
  builder->CreateCondBr(cmp, loop_body, loop_exit);

  // --- Loop Body ---
  builder->SetInsertPoint(loop_body);

  std::vector<llvm::Value *> indices;
  indices.push_back(builder->getInt64(0)); // Dereference the pointer to array
  indices.push_back(idx_phi);              // Index into array
  llvm::Value *elem_ptr = builder->CreateInBoundsGEP(llvm_array_type, array_ptr,
                                                     indices, "elem_ptr");

  // If dims > 1 (e.g. int[2][3]), the element is an Array (int[3])
  // If dims == 1 (e.g. int[2]), the element is Primitive (int)
  std::shared_ptr<types::Type> element_type;

  if (dims.size() > 1) {
    // Create sub-array type (remove first dimension)
    std::vector<size_t> sub_dims(dims.begin() + 1, dims.end());
    element_type =
        std::make_shared<types::ArrayType>(type->getUnderlyingType(), sub_dims);
  } else {
    // Base type
    element_type = type->getUnderlyingType();
  }

  llvm::Value *val_to_print = elem_ptr;

  if (element_type->getKind() != types::TypeKind::kArray &&
      element_type->getKind() != types::TypeKind::kObject) {
    val_to_print = resolveValue(elem_ptr, element_type.get());
  }

  emitRecursivePrint(val_to_print, element_type.get(), true);

  llvm::Value *is_last =
      builder->CreateICmpEQ(idx_phi, builder->getInt64(outer_dim - 1));

  llvm::BasicBlock *print_comma = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "comma", printer_fn);
  llvm::BasicBlock *after_comma = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "next", printer_fn);

  builder->CreateCondBr(is_last, after_comma, print_comma);

  builder->SetInsertPoint(print_comma);
  builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr(", ")});
  builder->CreateBr(after_comma);

  builder->SetInsertPoint(after_comma);

  llvm::Value *next_val = builder->CreateAdd(idx_phi, builder->getInt64(1));
  idx_phi->addIncoming(next_val, after_comma);
  builder->CreateBr(loop_cond);

  builder->SetInsertPoint(loop_exit);
  builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr(" ]")});
  builder->CreateRetVoid();

  if (prev_block) {
    builder->SetInsertPoint(prev_block, prev_insert_point);
  }

  return printer_fn;
}

llvm::Function *
IRGenerator::getOrCreateObjectPrinter(types::CustomObjectType *type) {
  auto &builder = m_ir_gen_context.getLLVMBuilder();
  auto mod = m_ir_gen_context.getLLVMModule();

  std::string func_name = "fg_print_struct_" + type->getCustomTypeName();
  if (auto existing_fn = mod->getFunction(func_name)) {
    return existing_fn;
  }

  llvm::FunctionType *fn_type = llvm::FunctionType::get(
      builder->getVoidTy(), {builder->getInt8PtrTy()}, false);

  llvm::Function *printer_fn = llvm::Function::Create(
      fn_type, llvm::Function::InternalLinkage, func_name, mod);

  auto prev_block = builder->GetInsertBlock();
  auto prev_insert_point = builder->GetInsertPoint();

  llvm::BasicBlock *entry_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "entry", printer_fn);
  builder->SetInsertPoint(entry_block);

  llvm::Value *obj_void_ptr = printer_fn->getArg(0);

  // Cast i8* back to typed pointer (Node*) for GEP access
  llvm::Type *llvm_struct_type =
      m_ir_gen_context.getTypeBuilder()->getLLVMType(type);
  llvm::Value *obj_typed_ptr = builder->CreateBitCast(
      obj_void_ptr, llvm_struct_type->getPointerTo(), "typed_ptr");

  auto enter_fn = mod->getOrInsertFunction(
      "fg_print_enter_object",
      llvm::FunctionType::get(builder->getInt1Ty(), {builder->getInt8PtrTy()},
                              false));
  auto exit_fn = mod->getOrInsertFunction(
      "fg_print_exit_object",
      llvm::FunctionType::get(builder->getVoidTy(), {}, false));
  auto printf_fn = mod->getOrInsertFunction(
      std::string(constants::functions::kPrintf_fn),
      llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt8PtrTy()},
                              true));

  llvm::Value *can_print = builder->CreateCall(enter_fn, {obj_void_ptr});

  llvm::BasicBlock *print_body = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "body", printer_fn);
  llvm::BasicBlock *exit_block = llvm::BasicBlock::Create(
      *m_ir_gen_context.getLLVMContext(), "exit", printer_fn);

  builder->CreateCondBr(can_print, print_body, exit_block);

  builder->SetInsertPoint(print_body);

  const auto &field_types_map = type->getFieldTypesMap();
  size_t field_index = 0;
  size_t total_fields = field_types_map.size();

  for (const auto &[field_name, field_type] : field_types_map) {
    // Print "key: "
    builder->CreateCall(printf_fn,
                        {builder->CreateGlobalStringPtr(field_name + ": ")});

    // Get Field Address
    llvm::Value *field_ptr =
        builder->CreateStructGEP(llvm_struct_type, obj_typed_ptr,
                                 static_cast<unsigned int>(field_index));

    llvm::Value *val_to_print;

    if (field_type->getKind() == types::TypeKind::kObject) {
      val_to_print = builder->CreateLoad(m_ir_gen_context.getTypeBuilder()
                                             ->getLLVMType(field_type.get())
                                             ->getPointerTo(),
                                         field_ptr, field_name + "_ptr");
    } else {
      val_to_print = resolveValue(field_ptr, field_type.get());
    }

    emitRecursivePrint(val_to_print, field_type.get(), true);

    if (field_index < total_fields - 1) {
      builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr(", ")});
    }
    field_index++;
  }

  builder->CreateCall(exit_fn, {});
  builder->CreateBr(exit_block);

  builder->SetInsertPoint(exit_block);
  builder->CreateRetVoid();

  if (prev_block) {
    builder->SetInsertPoint(prev_block, prev_insert_point);
  }

  return printer_fn;
}

void IRGenerator::emitPrint(binding::BoundCallExpression *call_expression) {

  for (const auto &argument : call_expression->getArguments()) {
    DEBUG_LOG("Print function argument type: ", argument->getType()->getName());

    argument->accept(this);

    assert(m_last_value && "m_last_value is null");
    assert(m_last_type && "m_last_type is null");

    CODEGEN_DEBUG_LOG("Last Type", m_last_type->getName());

    llvm::Value *value_to_print = resolvePtr(m_last_value, m_last_type);

    emitRecursivePrint(value_to_print, m_last_type, false);
    clearLast();
  }
}

llvm::Value *IRGenerator::resolvePtr(llvm::Value *value, types::Type *type) {
  bool is_inline_object = false;
  if (auto *gep = llvm::dyn_cast<llvm::GEPOperator>(value)) {
    if (gep->getSourceElementType()->isArrayTy()) {
      is_inline_object = true;
    }
  }

  bool is_object =
      (type->getKind() == types::TypeKind::kObject ||
       type->getKind() == types::TypeKind::kClass) &&
      !is_inline_object &&
      (llvm::isa<llvm::AllocaInst>(value) ||
       llvm::isa<llvm::GEPOperator>(value) ||
       llvm::isa<llvm::GlobalVariable>(value));

  bool is_inline_array = false;
  if (auto *alloca = llvm::dyn_cast<llvm::AllocaInst>(value)) {
    is_inline_array = (type->getKind() == types::TypeKind::kArray) &&
                      !alloca->getAllocatedType()->isPointerTy();
  } else if (llvm::isa<llvm::Argument>(value)) {
    // inout array params are passed as direct array pointers — always inline
    is_inline_array = (type->getKind() == types::TypeKind::kArray);
  }

  bool is_ptr_slot_array = (type->getKind() == types::TypeKind::kArray) &&
                           !is_inline_array &&
                           (llvm::isa<llvm::GlobalVariable>(value) ||
                            llvm::isa<llvm::AllocaInst>(value));

  if (is_inline_array) {
    return value;
  }

  if (is_object || is_ptr_slot_array) {
    llvm::Type *ptr_ptr_type =
        m_ir_gen_context.getTypeBuilder()->getLLVMType(type)->getPointerTo();
    return m_ir_gen_context.getLLVMBuilder()->CreateLoad(
        ptr_ptr_type, value,
        is_ptr_slot_array ? "array_load" : "field_obj_load");
  }

  return resolveValue(m_last_value, type);
}

void IRGenerator::emitCast(
    binding::BoundCallExpression *call_expression, types::Type *target_type,
    std::function<llvm::Value *(llvm::Value *, llvm::Type *)> converter) {

  const auto &argument = call_expression->getArguments()[0];
  argument->accept(this);

  assert(m_last_value && "m_last_value is null");

  if (m_last_type->isDynamic()) {
    auto &builder = m_ir_gen_context.getLLVMBuilder();
    auto *module = m_ir_gen_context.getLLVMModule();

    llvm::Value *dyn_ptr = ensurePointer(m_last_value, m_last_type, "dyn_cast_ptr");
    llvm::Function *unbox_fn = nullptr;

    if (target_type == analysis::Builtins::m_int8_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_int8_fn));
    } else if (target_type == analysis::Builtins::m_int32_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_int32_fn));
    } else if (target_type == analysis::Builtins::m_int64_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_int64_fn));
    } else if (target_type == analysis::Builtins::m_bool_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_bool_fn));
    } else if (target_type == analysis::Builtins::m_deci32_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_float32_fn));
    } else if (target_type == analysis::Builtins::m_deci_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_float64_fn));
    } else if (target_type == analysis::Builtins::m_char_type_instance.get()) {
      unbox_fn = module->getFunction(std::string(constants::functions::kUnbox_char_fn));
    } else {
      assert(false && "Unsupported dynamic unbox target type");
    }

    assert(unbox_fn && "Unbox function not found in module (ensure it is declared)");
    
    m_last_value = builder->CreateCall(unbox_fn, {dyn_ptr}, "unbox_result");
    m_last_type = target_type;
    return;
  }

  auto last_value = resolveValue(m_last_value, m_last_type);
  m_last_value = converter(last_value, last_value->getType());
  m_last_type = target_type;
}

void IRGenerator::dispatchBuiltinFunctionCall(
    binding::BoundCallExpression *call_expression) {
  auto function_symbol = call_expression->getSymbol();
  const std::string &fn_name = function_symbol->getName();

  CODEGEN_DEBUG_LOG("Visiting Built-In Function: ", fn_name);

  // Constants shortcuts
  namespace fns = constants::functions;

  if (fn_name == fns::kPrint_fn) {
    emitPrint(call_expression);
  } else if (fn_name == fns::kPrintln_fn) {
    emitPrint(call_expression);
    auto *mod = m_ir_gen_context.getLLVMModule();
    const std::unique_ptr<llvm::IRBuilder<>> &builder =
        m_ir_gen_context.getLLVMBuilder();
    auto *printf_fn =
        mod->getFunction(std::string(constants::functions::kPrintf_fn));
    builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("\n")});
  } else if (fn_name == fns::kString_fn) {
    const auto &argument = call_expression->getArguments()[0];
    argument->accept(this);
    assert(m_last_value && "m_last_value is null");
    assert(m_last_type && "m_last_type is null");
    if (m_last_type->isDynamic()) {
      auto &builder = m_ir_gen_context.getLLVMBuilder();
      auto *module = m_ir_gen_context.getLLVMModule();
      
      llvm::Value *dyn_ptr = ensurePointer(m_last_value, m_last_type, "dyn_str_ptr");
      llvm::Function *unbox_string_fn = module->getFunction("fg_unbox_string");
      assert(unbox_string_fn && "fg_unbox_string function not found in module");
      
      m_last_value = builder->CreateCall(unbox_string_fn, {dyn_ptr}, "unbox_str_result");
      m_last_type = analysis::Builtins::m_str_type_instance.get();
    }else {

      auto last_value = resolveValue(m_last_value, m_last_type);
      bool is_char =
          (m_last_type == analysis::Builtins::m_char_type_instance.get());
  
      m_last_value = convertToString(last_value, last_value->getType(), is_char);
      m_last_type = analysis::Builtins::m_str_type_instance.get();
    }
  } else if (fn_name == fns::kBool_fn) {
    emitCast(
        call_expression, analysis::Builtins::m_bool_type_instance.get(),
        [this](llvm::Value *v, llvm::Type *t) { return convertToBool(v, t); });
  } else if (fn_name == fns::kDecimal32_fn) {
    emitCast(
        call_expression, analysis::Builtins::m_deci32_type_instance.get(),
        [this](llvm::Value *v, llvm::Type *t) { return convertToFloat(v, t); });
  } else if (fn_name == fns::kDecimal_fn) {
    emitCast(call_expression, analysis::Builtins::m_deci_type_instance.get(),
             [this](llvm::Value *v, llvm::Type *t) {
               return convertToDouble(v, t);
             });
  } else if (fn_name == fns::kInt8_fn) {
    emitCast(
        call_expression, analysis::Builtins::m_int8_type_instance.get(),
        [this](llvm::Value *v, llvm::Type *t) { return convertToInt8(v, t); });
  } else if (fn_name == fns::kInt32_fn) {
    emitCast(
        call_expression, analysis::Builtins::m_int32_type_instance.get(),
        [this](llvm::Value *v, llvm::Type *t) { return convertToInt32(v, t); });
  } else if (fn_name == fns::kInt64_fn) {
    emitCast(
        call_expression, analysis::Builtins::m_int64_type_instance.get(),
        [this](llvm::Value *v, llvm::Type *t) { return convertToInt64(v, t); });
  } else if (fn_name == fns::kChar_fn) {
    emitCast(
        call_expression, analysis::Builtins::m_char_type_instance.get(),
        [this](llvm::Value *v, llvm::Type *t) { return convertToChar(v, t); });
  } else {
    assert(false && "Unknown builtin function dispatched");
  }
}

} // namespace flow_wing::ir_gen