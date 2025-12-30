/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
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

      std::vector<llvm::Value *> arguments;

      for (const auto &argument : call_expression->getArguments()) {

        DEBUG_LOG("Print function argument type: ",
                  argument->getType()->getName());

        argument->accept(this);

        assert(m_last_value && "m_last_value is null");
        assert(m_last_type && "m_last_type is null");

        bool is_char =
            (m_last_type == analysis::Builtins::m_char_type_instance.get());

        m_ir_gen_context.getLLVMBuilder()->CreateCall(
            printf_function,
            {convertToString(m_last_value, m_last_value->getType(), is_char)});
        clearLastValue();
      }
    };

    auto stringFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];

      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      assert(m_last_type && "m_last_type is null");

      bool is_char =
          m_last_type == analysis::Builtins::m_char_type_instance.get();

      m_last_value =
          convertToString(m_last_value, m_last_value->getType(), is_char);
      m_last_type = analysis::Builtins::m_str_type_instance.get();
    };

    auto boolFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToBool(m_last_value, m_last_value->getType());
      m_last_type = analysis::Builtins::m_bool_type_instance.get();
    };

    auto deci32Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToFloat(m_last_value, m_last_value->getType());
      m_last_type = analysis::Builtins::m_deci32_type_instance.get();
    };

    auto deciFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToDouble(m_last_value, m_last_value->getType());
      m_last_type = analysis::Builtins::m_deci_type_instance.get();
    };
    auto int8Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToInt8(m_last_value, m_last_value->getType());
      m_last_type = analysis::Builtins::m_int8_type_instance.get();
    };

    auto int32Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToInt32(m_last_value, m_last_value->getType());
      m_last_type = analysis::Builtins::m_int32_type_instance.get();
    };

    auto int64Fn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToInt64(m_last_value, m_last_value->getType());
      m_last_type = analysis::Builtins::m_int64_type_instance.get();
    };

    auto charFn = [&](binding::BoundCallExpression *call_expression) {
      const auto &argument = call_expression->getArguments()[0];
      argument->accept(this);
      assert(m_last_value && "m_last_value is null");
      m_last_value = convertToChar(m_last_value, m_last_value->getType());
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