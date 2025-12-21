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

  if (analysis::Builtins::isBuiltInFunction(function_symbol->getName())) {

    CODEGEN_DEBUG_LOG("Visiting Built-In Function: ",
                      function_symbol->getName());

    if (function_symbol->getName() ==
        std::string(ir_gen::constants::functions::kPrint_fn)) {
      auto printf_function = m_ir_gen_context.getLLVMModule()->getFunction(
          std::string(ir_gen::constants::functions::kPrintf_fn));

      CODEGEN_DEBUG_LOG("printf_function", printf_function->getName().str());

      assert(printf_function && "kPrintf_fn function not found");

      std::vector<llvm::Value *> arguments;

      for (const auto &argument : call_expression->getArguments()) {
        argument->accept(this);

        assert(m_last_value && "m_last_value is null");

        m_ir_gen_context.getLLVMBuilder()->CreateCall(
            printf_function,
            {convertToString(m_last_value, m_last_value->getType())});
        clearLastValue();
      }
    }
  }
}
} // namespace flow_wing::ir_gen