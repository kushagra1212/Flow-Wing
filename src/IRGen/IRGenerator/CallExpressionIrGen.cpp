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
void IRGenerator::visit(binding::BoundCallExpression *call_expression) {
  CODEGEN_DEBUG_LOG("Visiting Bound Call Expression", "IR GENERATION");

  auto function_symbol = call_expression->getSymbol();

  auto callBuiltinFunction = [&](binding::BoundCallExpression
                                     *call_expression) {
    auto printFn = [&](binding::BoundCallExpression *call_expression) {
      auto printf_function = m_ir_gen_context.getLLVMModule()->getFunction(
          std::string(ir_gen::constants::functions::kPrintf_fn));

      CODEGEN_DEBUG_LOG("printf_function", printf_function->getName().str());

      assert(printf_function && "kPrintf_fn function not found");

      std::function<void(llvm::Value *, types::Type *, bool is_nested)>
          emitPrintRecursive;

      emitPrintRecursive = [&](llvm::Value *value, types::Type *type,
                               bool is_nested) {
        if (type->isDynamic()) {

          llvm::Function *print_dynamic_fn =
              m_ir_gen_context.getLLVMModule()->getFunction(
                  std::string(ir_gen::constants::functions::kPrint_dynamic_fn));
          assert(print_dynamic_fn && "kPrint_dynamic_fn not found");

          m_ir_gen_context.getLLVMBuilder()->CreateCall(print_dynamic_fn,
                                                        {value});

          return;
        }

        if (type->getKind() == types::TypeKind::kObject) {
          auto *custom_type = static_cast<types::CustomObjectType *>(type);

          m_ir_gen_context.getLLVMBuilder()->CreateCall(
              printf_function,
              {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("{ ")});

          const auto &field_types_map = custom_type->getFieldTypesMap();
          size_t total_fields = field_types_map.size();

          size_t field_count = 0;
          for (const auto &[field_name, field_type] : field_types_map) {

            // Print Field Name: "name: "
            std::string label = field_name + ": ";
            m_ir_gen_context.getLLVMBuilder()->CreateCall(
                printf_function,
                {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(
                    label)});

            llvm::Value *field_ptr =
                m_ir_gen_context.getLLVMBuilder()->CreateStructGEP(
                    m_ir_gen_context.getTypeBuilder()->getLLVMType(custom_type),
                    value, static_cast<unsigned int>(field_count));

            llvm::Value *loaded_field =
                m_ir_gen_context.getLLVMBuilder()->CreateLoad(
                    m_ir_gen_context.getTypeBuilder()->getLLVMType(
                        field_type.get()),
                    field_ptr, field_name + "_val_ptr");

            emitPrintRecursive(loaded_field, field_type.get(), true);

            if (field_count < total_fields - 1) {
              m_ir_gen_context.getLLVMBuilder()->CreateCall(
                  printf_function,
                  {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(
                      ", ")});
            }
            field_count++;
          }
          m_ir_gen_context.getLLVMBuilder()->CreateCall(
              printf_function,
              {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr(" }")});
          return;
        }

        bool is_string =
            (type == analysis::Builtins::m_str_type_instance.get());
        bool is_char = (type == analysis::Builtins::m_char_type_instance.get());

        if (is_nested && is_string) {
          m_ir_gen_context.getLLVMBuilder()->CreateCall(
              printf_function,
              {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("\"")});
        }
        if (is_nested && is_char) {
          m_ir_gen_context.getLLVMBuilder()->CreateCall(
              printf_function,
              {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("'")});
        }

        llvm::Value *stringified_value =
            convertToString(value, value->getType(), is_char);

        m_ir_gen_context.getLLVMBuilder()->CreateCall(printf_function,
                                                      {stringified_value});

        if (is_nested && is_string) {
          m_ir_gen_context.getLLVMBuilder()->CreateCall(
              printf_function,
              {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("\"")});
        }
        if (is_nested && is_char) {
          m_ir_gen_context.getLLVMBuilder()->CreateCall(
              printf_function,
              {m_ir_gen_context.getLLVMBuilder()->CreateGlobalStringPtr("'")});
        }
      };

      std::vector<llvm::Value *> arguments;

      for (const auto &argument : call_expression->getArguments()) {

        DEBUG_LOG("Print function argument type: ",
                  argument->getType()->getName());

        argument->accept(this);

        assert(m_last_value && "m_last_value is null");
        assert(m_last_type && "m_last_type is null");

        llvm::Value *value_to_print = m_last_value;
        if (m_last_type->getKind() != types::TypeKind::kObject &&
            !m_last_type->isDynamic()) {
          value_to_print = resolveValue(m_last_value, m_last_type);
        }

        emitPrintRecursive(value_to_print, m_last_type, false);

        clearLast();
      }
    };

    auto stringFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];

      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      assert(m_last_type && "m_last_type is null");

      auto last_value = resolveValue(m_last_value, m_last_type);

      bool is_char =
          m_last_type == analysis::Builtins::m_char_type_instance.get();

      m_last_value =
          convertToString(last_value, last_value->getType(), is_char);
      m_last_type = analysis::Builtins::m_str_type_instance.get();
    };

    auto boolFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");

      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToBool(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_bool_type_instance.get();
    };

    auto deci32Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToFloat(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_deci32_type_instance.get();
    };

    auto deciFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToDouble(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_deci_type_instance.get();
    };
    auto int8Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToInt8(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_int8_type_instance.get();
    };

    auto int32Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToInt32(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_int32_type_instance.get();
    };

    auto int64Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToInt64(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_int64_type_instance.get();
    };

    auto charFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      auto last_value = resolveValue(m_last_value, m_last_type);
      m_last_value = convertToChar(last_value, last_value->getType());
      m_last_type = analysis::Builtins::m_char_type_instance.get();
    };

    CODEGEN_DEBUG_LOG("Visiting Built-In Function: ",
                      function_symbol->getName());

    std::unordered_map<std::string,
                       std::function<void(binding::BoundCallExpression *)>>
        builtinFunctions = {
            {std::string(ir_gen::constants::functions::kPrint_fn), printFn},
            {std::string(ir_gen::constants::functions::kString_fn), stringFn},
            {std::string(ir_gen::constants::functions::kBool_fn), boolFn},
            {std::string(ir_gen::constants::functions::kDecimal32_fn),
             deci32Fn},
            {std::string(ir_gen::constants::functions::kDecimal_fn), deciFn},
            {std::string(ir_gen::constants::functions::kInt32_fn), int32Fn},
            {std::string(ir_gen::constants::functions::kInt8_fn), int8Fn},
            {std::string(ir_gen::constants::functions::kInt64_fn), int64Fn},
            {std::string(ir_gen::constants::functions::kChar_fn), charFn}};

    builtinFunctions[function_symbol->getName()](call_expression);
  };

  if (analysis::Builtins::isBuiltInFunction(function_symbol->getName())) {
    callBuiltinFunction(call_expression);
  }
}
} // namespace flow_wing::ir_gen