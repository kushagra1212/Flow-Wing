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

#include "ExpressionBinder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIdentifierExpression/BoundIdentifierExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundParenthesizedExpression/BoundParenthesizedExpression.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/MemberAccessExpressionSyntax/MemberAccessExpressionSyntax.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"
#include "src/syntax/expression/SuperExpressionSyntax/SuperExpressionSyntax.h"
#include "src/utils/LogConfig.h"
#include <cassert>
#include <string>

namespace flow_wing {
namespace binding {

std::unique_ptr<BoundExpression>
ExpressionBinder::bindCallExpression(syntax::CallExpressionSyntax *expression) {
  assert(expression != nullptr &&
         "CallExpressionBinder::bind: expression is null");

  auto identifier_expression = expression->getIdentifier().get();

  // Handle member function calls: obj.method(args)
  if (identifier_expression->getKind() ==
      syntax::NodeKind::kMemberAccessExpression) {
    return bindMemberFunctionCall(expression);
  }

  if (identifier_expression->getKind() == syntax::NodeKind::kSuperExpression) {
    return bindSuperInitCall(expression);
  }

  std::string callee_display_name;
  analysis::Symbol *pre_resolved_callee = nullptr;

  if (identifier_expression->getKind() ==
      syntax::NodeKind::kIdentifierExpression) {
    callee_display_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(identifier_expression)
            ->getValue();
  } else if (identifier_expression->getKind() ==
             syntax::NodeKind::kModuleAccessExpression) {
    auto *ma = static_cast<syntax::ModuleAccessExpressionSyntax *>(
        identifier_expression);
    auto *mod_syn = ma->getModuleNameExpression().get();
    auto *mem_syn = ma->getMemberAccessExpression().get();
    if (mod_syn->getKind() != syntax::NodeKind::kIdentifierExpression ||
        mem_syn->getKind() != syntax::NodeKind::kIdentifierExpression) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kUnexpectedExpression,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              syntax::toString(identifier_expression->getKind()),
              "module::name (simple identifier after ::)"});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
    const std::string &mod_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(mod_syn)->getValue();
    callee_display_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(mem_syn)->getValue();
    auto module_sym_sh = m_context->getSymbolTable()->lookup(mod_name);
    if (!module_sym_sh ||
        module_sym_sh->getKind() != analysis::SymbolKind::kModule) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          mod_syn->getSourceLocation(),
          diagnostic::DiagnosticCode::kModuleNotFound,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{mod_name});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
    auto *module_symbol =
        static_cast<analysis::ModuleSymbol *>(module_sym_sh.get());
    auto saved = m_context->getSymbolTable();
    m_context->switchSymbolTable(module_symbol->getModuleSymbolTable());
    auto mem_sym = m_context->getSymbolTable()->lookup(callee_display_name);
    auto is_built_in_fn =
        analysis::Builtins::isBuiltInFunction(callee_display_name);
    m_context->switchSymbolTable(saved);
    if (!mem_sym || is_built_in_fn) {
      auto error_expression = std::make_unique<BoundErrorExpression>(
          mem_syn->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionNotFound,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              mod_name + "::" + callee_display_name});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
    pre_resolved_callee = mem_sym.get();
  } else {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kUnexpectedExpression,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            syntax::toString(identifier_expression->getKind()),
            syntax::toString(syntax::NodeKind::kIdentifierExpression)});

    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  // `init` is only invoked by `new Class(...)`; explicit calls are invalid.
  if (callee_display_name == "init") {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kInvalidInitFunctionCall,
        diagnostic::DiagnosticArgs{});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto handleCallExpression = [&](analysis::Symbol *symbol) {
    return bindCallToSymbol(expression, symbol, callee_display_name);
  };

  // A variable (or a field) of a function type holds a function value; the
  // call goes to the function it holds.
  auto holdsFunctionValue = [](const analysis::Symbol *symbol) {
    return symbol != nullptr &&
           symbol->getKind() == analysis::SymbolKind::kVariable &&
           symbol->getType() != nullptr &&
           symbol->getType()->getKind() == types::TypeKind::kFunction;
  };

  std::unique_ptr<BoundExpression> result;
  if (pre_resolved_callee) {
    result = holdsFunctionValue(pre_resolved_callee)
                 ? bindCallThroughValue(expression, bind(identifier_expression),
                                        callee_display_name)
                 : handleCallExpression(pre_resolved_callee);
  } else {
    auto builtins_symbol_itr =
        analysis::Builtins::m_functions_symbols_map.find(callee_display_name);

    if (builtins_symbol_itr !=
        analysis::Builtins::m_functions_symbols_map.end()) {

      DEBUG_LOG("Builtins Symbol Itr", "Builtins Symbol Itr",
                builtins_symbol_itr->second.size());
      for (const auto &symbol : builtins_symbol_itr->second) {

        result = handleCallExpression(symbol.get());
        if (result->getKind() != NodeKind::kErrorExpression) {
          break;
        }
        result = nullptr;
      }
    }

    if (!result) {
      auto symbols = m_context->getSymbolTable()->lookup(callee_display_name);
      // Inside a method, `op(x)` may name a field of the class, as `op` alone
      // does (bindIdentifierExpression), unless a local of that name hides it.
      std::shared_ptr<analysis::Symbol> field;
      auto current_class = std::dynamic_pointer_cast<types::ClassType>(
          m_context->getCurrentClassType());
      if (current_class && m_context->getSymbolTable()->lookup("self")) {
        field = current_class->lookupField(callee_display_name);
      }
      const bool is_field_value =
          holdsFunctionValue(field.get()) && (!symbols || symbols == field);
      if (holdsFunctionValue(symbols.get()) || is_field_value) {
        result = bindCallThroughValue(expression, bind(identifier_expression),
                                      callee_display_name);
      } else {
        result = handleCallExpression(symbols.get());
      }
    }
  }

  if (result->getKind() == NodeKind::kErrorExpression &&
      callee_display_name != "init") {
    auto self_sh = m_context->getSymbolTable()->lookup("self");
    auto ct = std::dynamic_pointer_cast<types::ClassType>(
        m_context->getCurrentClassType());
    if (self_sh && ct) {
      auto argument_expression = expression->getArgumentExpression().get();
      std::vector<syntax::ExpressionSyntax *> syntax_flat;
      if (argument_expression) {
        syntax_flat = flattenCommaExpressionList(argument_expression);
      }
      std::vector<std::unique_ptr<BoundExpression>> arguments;
      std::vector<std::shared_ptr<types::Type>> argument_types;
      bool arg_ok = true;
      if (argument_expression) {
        arguments = bindExpressionList(argument_expression);
        for (auto &argument : arguments) {
          if (argument->getKind() == NodeKind::kErrorExpression) {
            arg_ok = false;
            break;
          }
          argument_types.push_back(argument->getType());
        }
      }
      if (arg_ok) {
        auto member_symbol =
            ct->resolveMethodForCall(callee_display_name, argument_types);
        if (member_symbol &&
            member_symbol->getKind() == analysis::SymbolKind::kFunction) {
          auto *function_symbol =
              static_cast<analysis::FunctionSymbol *>(member_symbol.get());
          auto *function_type = static_cast<types::FunctionType *>(
              function_symbol->getType().get());
          const auto &param_types = function_type->getParameterTypes();
          for (size_t i = 0; i < arguments.size() && i < param_types.size();
               ++i) {
            if (i < syntax_flat.size() && param_types[i] &&
                param_types[i]->type->getKind() == types::TypeKind::kObject &&
                syntax_flat[i]->getKind() ==
                    syntax::NodeKind::kObjectExpression) {
              auto reb = bindObjectExpression(
                  static_cast<syntax::ObjectExpressionSyntax *>(syntax_flat[i]),
                  param_types[i]->type);
              if (reb->getKind() != NodeKind::kErrorExpression) {
                arguments[i] = std::move(reb);
                argument_types[i] = arguments[i]->getType();
              }
            }
          }
          auto self_expr = std::make_unique<BoundIdentifierExpression>(
              self_sh.get(), expression->getSourceLocation());
          arguments.push_back(std::move(self_expr));
          auto call = std::make_unique<BoundCallExpression>(
              function_symbol, std::move(arguments),
              expression->getSourceLocation());
          call->setImplicitReceiverLast(true);
          const int slot = ct->getVirtualSlotForMethod(function_symbol);
          if (slot >= 0)
            call->setVirtualDispatch(true, static_cast<std::size_t>(slot));
          result = std::move(call);
        }
      }
    }
  }

  if (result->getKind() == NodeKind::kErrorExpression) {

    m_context->reportError(static_cast<BoundErrorExpression *>(result.get()));
  }

  return result;
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindCallToSymbol(
    syntax::CallExpressionSyntax *expression, analysis::Symbol *symbol,
    const std::string &callee_display_name) {
  auto identifier_expression = expression->getIdentifier().get();

  if (!symbol) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kFunctionNotFound,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            callee_display_name});

    return std::move(error_expression);
  }

  BINDER_DEBUG_LOG("_Symbol", symbol->getName(),
                   symbol->getKind() == analysis::SymbolKind::kParameter,
                   types::Type::toString(symbol->getType()->getKind()));

  analysis::FunctionSymbol *function_symbol = nullptr;

  if (symbol->getKind() == analysis::SymbolKind::kParameter) {
    auto parameter_symbol = static_cast<analysis::ParameterSymbol *>(symbol);
    if (!parameter_symbol->getFunctionSymbol()) {

      auto error_expression = std::make_unique<BoundErrorExpression>(
          identifier_expression->getSourceLocation(),
          diagnostic::DiagnosticCode::kTypeIsNotAFunction,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              symbol->getType() ? symbol->getType()->getName()
                                : callee_display_name});
      return std::move(error_expression);
    } else {
      function_symbol = static_cast<analysis::FunctionSymbol *>(
          parameter_symbol->getFunctionSymbol().get());
    }
  } else if (symbol->getKind() != analysis::SymbolKind::kFunction) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kTypeIsNotAFunction,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            symbol->getType() ? symbol->getType()->getName()
                              : callee_display_name});
    return std::move(error_expression);
  } else {
    function_symbol = static_cast<analysis::FunctionSymbol *>(symbol);
  }

  assert(function_symbol != nullptr && "Function Symbol is null");

  BINDER_DEBUG_LOG("Function Symbol2", function_symbol->getName(),
                   function_symbol->getKind() ==
                       analysis::SymbolKind::kFunction);

  auto type = function_symbol->getType();

  if (type->getKind() != types::TypeKind::kFunction) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kTypeIsNotAFunction,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{type->getName()});

    return std::move(error_expression);
  }

  auto function_type = static_cast<types::FunctionType *>(type.get());
  DEBUG_LOG("Function Type", "Function Type", function_type->getName());

  const auto &param_types = function_type->getParameterTypes();

  auto argument_expression = expression->getArgumentExpression().get();

  std::vector<std::unique_ptr<BoundExpression>> arguments;
  std::vector<std::shared_ptr<types::Type>> argument_types;

  if (argument_expression) {
    arguments = bindCallArgumentList(argument_expression, param_types);
    for (auto &argument : arguments) {
      if (argument->getKind() == NodeKind::kErrorExpression) {
        return std::move(argument);
      }
      argument_types.push_back(argument->getType());
    }
  }

  auto const has_default_value =
      function_type->getDefaultValueStartIndex() != static_cast<size_t>(-1);

  if (has_default_value &&
      argument_types.size() < function_type->getDefaultValueStartIndex()) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            callee_display_name + "(" + function_type->getName() + ")",
            std::to_string(function_type->getDefaultValueStartIndex()),
            std::to_string(arguments.size()),
        });

    return std::move(error_expression);
  }

  if (!has_default_value &&
      argument_types.size() != function_type->getParameterTypes().size() &&
      !function_type->isVariadic()) {

    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
        std::vector<flow_wing::diagnostic::DiagnosticArg>{
            callee_display_name + "(" + function_type->getName() + ")",
            std::to_string(function_type->getParameterTypes().size()),
            std::to_string(arguments.size()),
        });

    return std::move(error_expression);
  }

  auto const size = arguments.size();

  for (size_t i = 0; i < size; i++) {
    if (arguments[i]->getType()->isNthg()) {
      types::Type *expected_type = nullptr;
      if (!param_types.empty()) {
        expected_type = i < param_types.size()
                            ? param_types[i]->type.get()
                            : param_types.back()->type.get();
      } else {
        // Variadic builtins like print() / println() have no formal
        // parameters in the type signature; avoid param_types.back() on an
        // empty vector.
        expected_type = analysis::Builtins::m_dynamic_type_instance.get();
      }
      auto error_expression = std::make_unique<BoundErrorExpression>(
          arguments[i]->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
          std::vector<flow_wing::diagnostic::DiagnosticArg>{
              expected_type->getName(), arguments[i]->getType()->getName(),
              callee_display_name + "(" + function_type->getName() + ")"});
      return std::move(error_expression);
    }
  }

  if (!function_type->isVariadic()) {
    for (size_t i = 0; i < size; i++) {
      auto param = param_types[i];
      auto parameter_type = param->type;
      auto argument_type = arguments[i]->getType();

      DEBUG_LOG("Argument Type", "Argument Type", argument_type->getName());
      DEBUG_LOG("Parameter Type", "Parameter Type",
                parameter_type->getName());

      // inout parameters require an lvalue (variable, index, or member
      // access)
      if (param->value_kind == types::ValueKind::kByReference) {
        const BoundExpression *e = arguments[i].get();
        while (e && e->getKind() == NodeKind::kParenthesizedExpression) {
          e = static_cast<const BoundParenthesizedExpression *>(e)
                  ->getExpression()
                  .get();
        }
        const bool is_lvalue =
            e && (e->getKind() == NodeKind::kIdentifierExpression ||
                  e->getKind() == NodeKind::kIndexExpression ||
                  e->getKind() == NodeKind::kMemberAccessExpression);
        if (!is_lvalue) {
          auto error_expression = std::make_unique<BoundErrorExpression>(
              arguments[i]->getSourceLocation(),
              diagnostic::DiagnosticCode::
                  kLiteralCannotBePassedToInoutParameter,
              std::vector<flow_wing::diagnostic::DiagnosticArg>{
                  callee_display_name + "(" + function_type->getName() +
                  ")"});
          return std::move(error_expression);
        }
      }

      if (*argument_type > *parameter_type) {

        auto error_expression = std::make_unique<BoundErrorExpression>(
            arguments[i]->getSourceLocation(),
            diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
            std::vector<flow_wing::diagnostic::DiagnosticArg>{
                parameter_type->getName(), argument_type->getName(),
                callee_display_name + "(" + function_type->getName() + ")"});

        return std::move(error_expression);
      }
    }
  }

  return std::make_unique<BoundCallExpression>(
      function_symbol, std::move(arguments), expression->getSourceLocation());
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindCallThroughValue(
    syntax::CallExpressionSyntax *expression,
    std::unique_ptr<BoundExpression> callee,
    const std::string &callee_display_name) {
  if (callee->getKind() == NodeKind::kErrorExpression) {
    return callee;
  }

  // This symbol only describes the call: it has the value's type, and it is
  // marked indirect, so code generation calls what `callee` yields instead of
  // looking up a function by this name.
  auto function_symbol = std::make_shared<analysis::FunctionSymbol>(
      callee_display_name, callee->getType(), /*is_parameter_symbol=*/true);

  auto result =
      bindCallToSymbol(expression, function_symbol.get(), callee_display_name);
  if (result->getKind() == NodeKind::kCallExpression) {
    static_cast<BoundCallExpression *>(result.get())
        ->setCallee(std::move(callee), std::move(function_symbol));
  }
  return result;
}

std::unique_ptr<BoundExpression> ExpressionBinder::bindMemberFunctionCall(
    syntax::CallExpressionSyntax *expression) {

  auto *member_access = static_cast<syntax::MemberAccessExpressionSyntax *>(
      expression->getIdentifier().get());

  auto bound_object = bind(member_access->getLeftExpression().get());
  if (bound_object->getKind() == NodeKind::kErrorExpression) {
    return bound_object;
  }

  auto object_type = bound_object->getType();

  // A field that holds a function value, of a class (`box.op(x)`) or of an
  // object type (`handlers.onValue(x)`): call the function it holds.
  if (member_access->getRightExpression()->getKind() ==
      syntax::NodeKind::kIdentifierExpression) {
    const std::string &field_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(
            member_access->getRightExpression().get())
            ->getValue();
    std::shared_ptr<types::Type> field_type;
    if (object_type->getKind() == types::TypeKind::kClass) {
      auto field = static_cast<types::ClassType *>(object_type.get())
                       ->lookupField(field_name);
      if (field) {
        field_type = field->getType();
      }
    } else if (object_type->getKind() == types::TypeKind::kObject) {
      const auto &fields = static_cast<types::CustomObjectType *>(
                               object_type.get())
                               ->getFieldTypesMap();
      auto it = fields.find(field_name);
      if (it != fields.end()) {
        field_type = it->second;
      }
    }
    if (field_type && field_type->getKind() == types::TypeKind::kFunction) {
      auto result =
          bindCallThroughValue(expression, bind(member_access), field_name);
      if (result->getKind() == NodeKind::kErrorExpression) {
        m_context->reportError(static_cast<BoundErrorExpression *>(result.get()));
      }
      return result;
    }
  }

  if (object_type->getKind() != types::TypeKind::kClass) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        member_access->getLeftExpression()->getSourceLocation(),
        diagnostic::DiagnosticCode::kMemberAccessOnNonObjectVariable,
        diagnostic::DiagnosticArgs{object_type->getName()});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto *class_type = static_cast<types::ClassType *>(object_type.get());

  auto *member_id = static_cast<syntax::IdentifierExpressionSyntax *>(
      member_access->getRightExpression().get());
  const auto &method_name = member_id->getValue();

  if (method_name == "init") {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        member_id->getSourceLocation(),
        diagnostic::DiagnosticCode::kInvalidInitFunctionCall,
        diagnostic::DiagnosticArgs{});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  // Bind explicit arguments
  std::vector<std::unique_ptr<BoundExpression>> arguments;
  std::vector<std::shared_ptr<types::Type>> argument_types;

  auto argument_expression = expression->getArgumentExpression().get();
  std::vector<syntax::ExpressionSyntax *> syntax_flat;
  if (argument_expression) {
    syntax_flat = flattenCommaExpressionList(argument_expression);
  }
  if (argument_expression) {
    arguments = bindExpressionList(argument_expression);
    for (auto &argument : arguments) {
      if (argument->getKind() == NodeKind::kErrorExpression) {
        return std::move(argument);
      }
      argument_types.push_back(argument->getType());
    }
  }

  auto member_symbol =
      class_type->resolveMethodForCall(method_name, argument_types);
  if (!member_symbol) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        member_id->getSourceLocation(),
        diagnostic::DiagnosticCode::kFunctionNotFound,
        diagnostic::DiagnosticArgs{method_name});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto *function_symbol =
      static_cast<analysis::FunctionSymbol *>(member_symbol.get());
  auto *function_type =
      static_cast<types::FunctionType *>(function_symbol->getType().get());

  const auto &param_types = function_type->getParameterTypes();

  for (size_t i = 0; i < arguments.size() && i < param_types.size(); ++i) {
    if (i < syntax_flat.size() && param_types[i] &&
        param_types[i]->type->getKind() == types::TypeKind::kObject &&
        syntax_flat[i]->getKind() == syntax::NodeKind::kObjectExpression) {
      auto reb = bindObjectExpression(
          static_cast<syntax::ObjectExpressionSyntax *>(syntax_flat[i]),
          param_types[i]->type);
      if (reb->getKind() != NodeKind::kErrorExpression) {
        arguments[i] = std::move(reb);
        argument_types[i] = arguments[i]->getType();
      }
    }
  }

  for (size_t i = 0; i < arguments.size(); i++) {
    if (arguments[i]->getType()->isNthg()) {
      auto *expected_type = param_types[i]->type.get();
      auto error_expression = std::make_unique<BoundErrorExpression>(
          arguments[i]->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
          diagnostic::DiagnosticArgs{expected_type->getName(),
                                     arguments[i]->getType()->getName(),
                                     method_name});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
  }

  if (!function_type->isVariadic()) {
    for (size_t i = 0; i < arguments.size(); i++) {
      auto parameter_type = param_types[i]->type;
      auto argument_type = arguments[i]->getType();

      if (param_types[i]->value_kind == types::ValueKind::kByReference) {
        const BoundExpression *e = arguments[i].get();
        while (e && e->getKind() == NodeKind::kParenthesizedExpression) {
          e = static_cast<const BoundParenthesizedExpression *>(e)
                  ->getExpression()
                  .get();
        }
        const bool is_lvalue =
            e && (e->getKind() == NodeKind::kIdentifierExpression ||
                  e->getKind() == NodeKind::kIndexExpression ||
                  e->getKind() == NodeKind::kMemberAccessExpression);
        if (!is_lvalue) {
          auto error_expression = std::make_unique<BoundErrorExpression>(
              arguments[i]->getSourceLocation(),
              diagnostic::DiagnosticCode::
                  kLiteralCannotBePassedToInoutParameter,
              diagnostic::DiagnosticArgs{method_name + "(" +
                                         function_type->getName() + ")"});
          m_context->reportError(error_expression.get());
          return std::move(error_expression);
        }
      }

      if (*argument_type > *parameter_type) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            arguments[i]->getSourceLocation(),
            diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
            diagnostic::DiagnosticArgs{parameter_type->getName(),
                                       argument_type->getName(), method_name});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }
    }
  }

  // Append the receiver as the implicit self (last) argument
  arguments.push_back(std::move(bound_object));

  auto call = std::make_unique<BoundCallExpression>(
      function_symbol, std::move(arguments), expression->getSourceLocation());
  call->setImplicitReceiverLast(true);

  // Virtual for every receiver, `self` included: in a base class's method,
  // `self.area()` must reach the override of the object's own class, as a
  // bare `area()` does (the implicit-self path in bindCallExpression). `new`
  // stores the vtable pointer before `init` runs, so this holds in `init` too.
  if (method_name != "init") {
    const int slot = class_type->getVirtualSlotForMethod(function_symbol);
    if (slot >= 0)
      call->setVirtualDispatch(true, static_cast<std::size_t>(slot));
  }

  return call;
}

std::unique_ptr<BoundExpression>
ExpressionBinder::bindSuperInitCall(syntax::CallExpressionSyntax *expression) {
  auto *identifier_expression = expression->getIdentifier().get();

  const analysis::FunctionSymbol *cur_fn =
      m_context->getSymbolTable()->getCurrentFunctionSymbol();
  if (!cur_fn || cur_fn->getName() != "init") {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kSuperCallOutsideConstructor,
        diagnostic::DiagnosticArgs{});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto ct = std::dynamic_pointer_cast<types::ClassType>(
      m_context->getCurrentClassType());
  if (!ct) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kSuperCallOutsideConstructor,
        diagnostic::DiagnosticArgs{});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto base = ct->getBaseClass();
  if (!base) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kClassMissingSuperclass,
        diagnostic::DiagnosticArgs{ct->getName()});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto argument_expression = expression->getArgumentExpression().get();
  std::vector<std::unique_ptr<BoundExpression>> arguments;
  std::vector<std::shared_ptr<types::Type>> argument_types;

  if (argument_expression) {
    arguments = bindExpressionList(argument_expression);
    for (auto &argument : arguments) {
      if (argument->getKind() == NodeKind::kErrorExpression) {
        return std::move(argument);
      }
      argument_types.push_back(argument->getType());
    }
  }

  auto member_symbol = base->resolveMethodForCall("init", argument_types);
  if (!member_symbol) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kFunctionNotFound,
        diagnostic::DiagnosticArgs{std::string("super")});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto *function_symbol =
      static_cast<analysis::FunctionSymbol *>(member_symbol.get());
  auto *function_type =
      static_cast<types::FunctionType *>(function_symbol->getType().get());

  const auto &param_types = function_type->getParameterTypes();
  const size_t visible_count = param_types.size() - 1;

  if (argument_types.size() > visible_count) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kFunctionArgumentCountMismatch,
        diagnostic::DiagnosticArgs{std::string("super"),
                                   std::to_string(visible_count),
                                   std::to_string(argument_types.size())});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  for (size_t i = 0; i < arguments.size(); i++) {
    if (arguments[i]->getType()->isNthg()) {
      auto *expected_type = param_types[i]->type.get();
      auto error_expression = std::make_unique<BoundErrorExpression>(
          arguments[i]->getSourceLocation(),
          diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
          diagnostic::DiagnosticArgs{expected_type->getName(),
                                     arguments[i]->getType()->getName(),
                                     std::string("super")});
      m_context->reportError(error_expression.get());
      return std::move(error_expression);
    }
  }

  if (!function_type->isVariadic()) {
    for (size_t i = 0; i < arguments.size(); i++) {
      auto parameter_type = param_types[i]->type;
      auto argument_type = arguments[i]->getType();
      if (*argument_type > *parameter_type) {
        auto error_expression = std::make_unique<BoundErrorExpression>(
            arguments[i]->getSourceLocation(),
            diagnostic::DiagnosticCode::kFunctionArgumentTypeMismatch,
            diagnostic::DiagnosticArgs{parameter_type->getName(),
                                       argument_type->getName(),
                                       std::string("super")});
        m_context->reportError(error_expression.get());
        return std::move(error_expression);
      }
    }
  }

  auto self_sh = m_context->getSymbolTable()->lookup("self");
  if (!self_sh) {
    auto error_expression = std::make_unique<BoundErrorExpression>(
        identifier_expression->getSourceLocation(),
        diagnostic::DiagnosticCode::kVariableNotFound,
        diagnostic::DiagnosticArgs{std::string("self")});
    m_context->reportError(error_expression.get());
    return std::move(error_expression);
  }

  auto self_expr = std::make_unique<BoundIdentifierExpression>(
      self_sh.get(), expression->getSourceLocation());
  arguments.push_back(std::move(self_expr));

  auto super_call = std::make_unique<BoundCallExpression>(
      function_symbol, std::move(arguments), expression->getSourceLocation());
  super_call->setImplicitReceiverLast(true);
  return super_call;
}

} // namespace binding
} // namespace flow_wing