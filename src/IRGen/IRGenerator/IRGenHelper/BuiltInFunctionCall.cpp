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
    builder->CreateCall(print_dyn_fn, {value});
    return;
  }

  if (type->getKind() == types::TypeKind::kObject) {
    auto *custom_type = static_cast<types::CustomObjectType *>(type);

    // Open brace
    builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr("{ ")});

    const auto &field_types_map = custom_type->getFieldTypesMap();
    size_t total_fields = field_types_map.size();
    size_t field_count = 0;

    for (const auto &[field_name, field_type] : field_types_map) {
      // Label: "name: "
      builder->CreateCall(printf_fn,
                          {builder->CreateGlobalStringPtr(field_name + ": ")});

      llvm::Value *struct_ptr = ensurePointer(value, custom_type, "print_tmp");

      llvm::Value *field_ptr = builder->CreateStructGEP(
          m_ir_gen_context.getTypeBuilder()->getLLVMType(custom_type),
          struct_ptr, static_cast<unsigned int>(field_count));

      llvm::Value *loaded_field = builder->CreateLoad(
          m_ir_gen_context.getTypeBuilder()->getLLVMType(field_type.get()),
          field_ptr, field_name + "_val_ptr");

      // Recursive call for field
      emitRecursivePrint(loaded_field, field_type.get(), true);

      if (field_count < total_fields - 1) {
        builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr(", ")});
      }
      field_count++;
    }

    builder->CreateCall(printf_fn, {builder->CreateGlobalStringPtr(" }")});
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

void IRGenerator::emitPrint(binding::BoundCallExpression *call_expression) {

  for (const auto &argument : call_expression->getArguments()) {
    DEBUG_LOG("Print function argument type: ", argument->getType()->getName());

    argument->accept(this);

    assert(m_last_value && "m_last_value is null");
    assert(m_last_type && "m_last_type is null");

    llvm::Value *value_to_print = m_last_value;

    // Resolve variable references unless it's an object or dynamic
    if (m_last_type->getKind() != types::TypeKind::kObject &&
        !m_last_type->isDynamic()) {
      value_to_print = resolveValue(m_last_value, m_last_type);
    }

    emitRecursivePrint(value_to_print, m_last_type, false);
    clearLast();
  }
}

void IRGenerator::emitCast(
    binding::BoundCallExpression *call_expression, types::Type *target_type,
    std::function<llvm::Value *(llvm::Value *, llvm::Type *)> converter) {

  const auto &argument = call_expression->getArguments()[0];
  argument->accept(this);

  assert(m_last_value && "m_last_value is null");

  auto last_value = resolveValue(m_last_value, m_last_type);
  m_last_value = converter(last_value, last_value->getType());
  m_last_type = target_type;
}

void IRGenerator::dispatchBuiltinFunction(
    binding::BoundCallExpression *call_expression) {
  auto function_symbol = call_expression->getSymbol();
  const std::string &fn_name = function_symbol->getName();

  CODEGEN_DEBUG_LOG("Visiting Built-In Function: ", fn_name);

  // Constants shortcuts
  namespace fns = constants::functions;

  if (fn_name == fns::kPrint_fn) {
    emitPrint(call_expression);
  } else if (fn_name == fns::kString_fn) {
    const auto &argument = call_expression->getArguments()[0];
    argument->accept(this);
    assert(m_last_value && "m_last_value is null");
    assert(m_last_type && "m_last_type is null");

    auto last_value = resolveValue(m_last_value, m_last_type);
    bool is_char =
        (m_last_type == analysis::Builtins::m_char_type_instance.get());

    m_last_value = convertToString(last_value, last_value->getType(), is_char);
    m_last_type = analysis::Builtins::m_str_type_instance.get();
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