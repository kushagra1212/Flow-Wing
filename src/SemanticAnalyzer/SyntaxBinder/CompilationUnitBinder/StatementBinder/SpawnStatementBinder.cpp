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

#include "StatementBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundSpawnStatement/BoundSpawnStatement.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/ExpressionBinder/ExpressionBinder.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/syntax/statements/SpawnStatementSyntax/SpawnStatementSyntax.h"
#include <cassert>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundStatement>
StatementBinder::bindSpawnStatement(syntax::SpawnStatementSyntax *statement) {
  assert(statement != nullptr &&
         "SpawnStatementBinder::bind: statement is null");

  auto reject = [&]() -> std::unique_ptr<BoundStatement> {
    auto error_statement = std::make_unique<BoundErrorStatement>(
        statement->getSourceLocation(),
        diagnostic::DiagnosticCode::kSpawnRequiresFunctionCall,
        diagnostic::DiagnosticArgs{});

    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  };

  if (statement->getCallExpression() == nullptr) {
    return reject();
  }

  auto bound_expression =
      m_expression_binder->bind(statement->getCallExpression().get());

  // Binding the call can fail on its own terms — wrong argument count, wrong
  // argument type, unknown name. Those come with a precise message and a
  // location that points at the offending argument. Adding "spawn expects a
  // function call" on top of one of them would bury the message that actually
  // tells the user what to change, so propagate the failure silently.
  if (bound_expression != nullptr &&
      bound_expression->getKind() == NodeKind::kErrorExpression) {
    return std::make_unique<BoundErrorStatement>(
        statement->getSourceLocation(),
        diagnostic::DiagnosticCode::kSpawnRequiresFunctionCall,
        diagnostic::DiagnosticArgs{});
  }

  // The parser accepts any expression after `spawn` so that a bad operand
  // reaches here with a real source location instead of dying as a parse error.
  if (bound_expression == nullptr ||
      bound_expression->getKind() != NodeKind::kCallExpression) {
    return reject();
  }

  std::unique_ptr<BoundCallExpression> call_expression(
      static_cast<BoundCallExpression *>(bound_expression.release()));

  const auto *function_symbol = call_expression->getSymbol();

  auto fail = [&](diagnostic::DiagnosticCode code)
      -> std::unique_ptr<BoundStatement> {
    auto error_statement = std::make_unique<BoundErrorStatement>(
        statement->getSourceLocation(), code, diagnostic::DiagnosticArgs{});

    m_context->reportError(error_statement.get());
    return std::move(error_statement);
  };

  // Methods first: `self` is a hidden argument, so the generic argument check
  // below would fire and blame the user for arguments they never wrote.
  if (call_expression->getImplicitReceiverLast() ||
      (function_symbol != nullptr &&
       function_symbol->getHideTrailingParamsForDisplay() > 0)) {
    return fail(diagnostic::DiagnosticCode::kSpawnRequiresPlainFunction);
  }

  // A built-in such as `println` is emitted inline by the compiler: no function
  // is added to the module, so there is no address for the scheduler to store,
  // and its declared parameter list does not describe the call's arguments
  // (print takes any number of them). IRGen looked up a function that does not
  // exist and then dereferenced the null result, which crashed the compiler on
  // `spawn println("hi")`. Reject it here, where the user gets a real message.
  if (function_symbol == nullptr || function_symbol->getType() == nullptr ||
      analysis::Builtins::isBuiltInFunction(function_symbol->getName())) {
    return fail(diagnostic::DiagnosticCode::kSpawnRequiresUserFunction);
  }

  // A value-returning function is `void f(T *out)` in IR — it takes a hidden
  // out-parameter. The scheduler calls tasks through `void (*)(void)`, so that
  // parameter would be garbage and the task would segfault. Only `nthg`
  // returns are callable with no arguments at all.
  {
    const auto *function_type =
        static_cast<const types::FunctionType *>(function_symbol->getType().get());
    const auto &return_types = function_type->getReturnTypes();

    const bool returns_nthg =
        return_types.empty() ||
        (return_types.size() == 1 && return_types[0] != nullptr &&
         return_types[0]->type != nullptr && return_types[0]->type->isNthg());

    if (!returns_nthg) {
      return fail(diagnostic::DiagnosticCode::kSpawnRequiresNthgReturn);
    }
  }

  // Arguments are supported. IRGen evaluates them at the spawn site into a
  // GC-traced block whose descriptor lists its pointer fields, and the
  // scheduler roots that block until the task runs — a queued task owns no
  // stack yet, so there is nowhere else to put them.
  //
  // By-reference (`inout`) arguments stay rejected: they alias a stack slot in
  // the spawning frame, and that frame is long gone by the time the task runs.
  {
    const auto *ft = static_cast<const types::FunctionType *>(
        function_symbol->getType().get());
    const auto &params = ft->getParameterTypes();
    const size_t n = call_expression->getArguments().size();

    for (size_t i = 0; i < n && i < params.size(); i++) {
      if (params[i]->value_kind == types::ValueKind::kByReference) {
        return fail(diagnostic::DiagnosticCode::kSpawnByReferenceArgument);
      }
    }
  }

  return std::make_unique<BoundSpawnStatement>(std::move(call_expression),
                                               statement->getSourceLocation());
}
} // namespace binding
} // namespace flow_wing
