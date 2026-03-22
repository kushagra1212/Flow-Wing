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
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundErrorExpression/BoundErrorExpression.hpp"
#include "src/SemanticAnalyzer/BoundExpressions/BoundNewExpression/BoundNewExpression.hpp"
#include "src/SemanticAnalyzer/NodeKind/NodeKind.h"
#include "src/common/Symbol/FunctionSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/diagnostics/DiagnosticCode.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/NewExpressionSyntax/NewExpressionSyntax.h"
#include "src/syntax/expression/ObjectExpressionSyntax/ObjectExpressionSyntax.h"

namespace flow_wing {
namespace binding {

namespace {

std::shared_ptr<types::Type> tryGetSingleInitFirstParamObjectType(
    types::ClassType *ct) {
  std::shared_ptr<types::Type> found;
  int matches = 0;
  for (const auto &sym : ct->getMethodOverloads("init")) {
    auto *ft = static_cast<const types::FunctionType *>(sym->getType().get());
    const auto &pts = ft->getParameterTypes();
    if (pts.size() < 2)
      continue;
    const size_t visible = pts.size() - 1;
    if (visible != 1)
      continue;
    if (!pts[0]->type ||
        pts[0]->type->getKind() != types::TypeKind::kObject)
      continue;
    found = pts[0]->type;
    matches++;
  }
  if (matches == 1)
    return found;
  return nullptr;
}

/// An init overload whose visible arity (excluding self) equals `n`.
static std::shared_ptr<analysis::FunctionSymbol>
findInitOverloadWithVisibleArity(types::ClassType *ct, size_t n) {
  for (const auto &sym : ct->getMethodOverloads("init")) {
    auto *ft = static_cast<const types::FunctionType *>(sym->getType().get());
    const auto &pts = ft->getParameterTypes();
    if (pts.size() >= 2 && pts.size() - 1 == n)
      return std::static_pointer_cast<analysis::FunctionSymbol>(sym);
  }
  return nullptr;
}

} // namespace

std::unique_ptr<BoundExpression>
ExpressionBinder::bindNewExpression(syntax::NewExpressionSyntax *node) {
  auto *inner_syntax = node->getExpression().get();
  const auto &location = node->getSourceLocation();

  if (inner_syntax->getKind() == syntax::NodeKind::kCallExpression) {
    auto *call_syntax =
        static_cast<syntax::CallExpressionSyntax *>(inner_syntax);
    auto *id_syntax = call_syntax->getIdentifier().get();
    if (id_syntax->getKind() != syntax::NodeKind::kIdentifierExpression) {
      auto err = std::make_unique<BoundErrorExpression>(
          id_syntax->getSourceLocation(),
          diagnostic::DiagnosticCode::kUnexpectedExpression,
          std::vector<diagnostic::DiagnosticArg>{
              syntax::toString(id_syntax->getKind()),
              syntax::toString(syntax::NodeKind::kIdentifierExpression)});
      m_context->reportError(err.get());
      return std::move(err);
    }
    auto class_name =
        static_cast<syntax::IdentifierExpressionSyntax *>(id_syntax)
            ->getValue();
    auto symbol = m_context->getSymbolTable()->lookup(class_name);
    if (!symbol ||
        symbol->getKind() != analysis::SymbolKind::kClass) {
      auto err = std::make_unique<BoundErrorExpression>(
          id_syntax->getSourceLocation(),
          diagnostic::DiagnosticCode::kTypeIsNotAFunction,
          std::vector<diagnostic::DiagnosticArg>{
              symbol ? symbol->getType()->getName() : class_name});
      m_context->reportError(err.get());
      return std::move(err);
    }
    auto bound_id = bind(id_syntax);
    if (bound_id->getKind() == NodeKind::kErrorExpression) {
      return bound_id;
    }
    auto class_type_ptr =
        std::dynamic_pointer_cast<types::ClassType>(symbol->getType());
    std::vector<std::unique_ptr<BoundExpression>> args;
    if (call_syntax->getArgumentExpression()) {
      auto *arg_root = call_syntax->getArgumentExpression().get();
      if (arg_root->getKind() == syntax::NodeKind::kObjectExpression &&
          class_type_ptr) {
        if (auto hint =
                tryGetSingleInitFirstParamObjectType(class_type_ptr.get())) {
          args.push_back(bindObjectExpression(
              static_cast<syntax::ObjectExpressionSyntax *>(arg_root), hint));
        } else {
          args = bindExpressionList(arg_root);
        }
      } else {
        args = bindExpressionList(arg_root);
      }
      for (auto &a : args) {
        if (a->getKind() == NodeKind::kErrorExpression) {
          return std::move(a);
        }
      }
    }
    std::vector<std::shared_ptr<types::Type>> ctor_arg_types;
    for (const auto &a : args) {
      ctor_arg_types.push_back(a->getType());
    }
    auto resolved_init =
        class_type_ptr->resolveMethodForCall("init", ctor_arg_types);
    const auto &init_overloads = class_type_ptr->getMethodOverloads("init");
    if (!init_overloads.empty() && !resolved_init) {
      auto with_arity =
          findInitOverloadWithVisibleArity(class_type_ptr.get(),
                                           ctor_arg_types.size());
      if (with_arity) {
        auto *ft = static_cast<const types::FunctionType *>(
            with_arity->getType().get());
        const auto &pts = ft->getParameterTypes();
        const auto *expected_t = pts[0]->type.get();
        const auto *got_t = ctor_arg_types[0].get();
        const std::string &cname = class_type_ptr->getName();
        auto err = std::make_unique<BoundErrorExpression>(
            location,
            diagnostic::DiagnosticCode::
                kNewExpressionConstructorArgumentTypeMismatch,
            std::vector<diagnostic::DiagnosticArg>{
                cname, expected_t ? expected_t->getName() : std::string("?"),
                got_t ? got_t->getName() : std::string("?")});
        m_context->reportError(err.get());
        return std::move(err);
      }
      int expected_visible = 0;
      if (!init_overloads.empty()) {
        auto *ft0 = static_cast<const types::FunctionType *>(
            init_overloads[0]->getType().get());
        const auto &pts0 = ft0->getParameterTypes();
        if (pts0.size() >= 2)
          expected_visible = static_cast<int>(pts0.size() - 1);
      }
      const std::string &cname = class_type_ptr->getName();
      auto err = std::make_unique<BoundErrorExpression>(
          location,
          diagnostic::DiagnosticCode::
              kNewExpressionConstructorArgumentCountMismatch,
          std::vector<diagnostic::DiagnosticArg>{
              cname, expected_visible,
              static_cast<int>(ctor_arg_types.size())});
      m_context->reportError(err.get());
      return std::move(err);
    }
    return std::make_unique<BoundNewExpression>(
        std::move(bound_id), std::move(args), location);
  }

  if (inner_syntax->getKind() == syntax::NodeKind::kIdentifierExpression) {
    auto expression = bind(inner_syntax);
    if (expression->getKind() == NodeKind::kErrorExpression) {
      return expression;
    }
    if (expression->getType()->getKind() != types::TypeKind::kClass) {
      auto err = std::make_unique<BoundErrorExpression>(
          inner_syntax->getSourceLocation(),
          diagnostic::DiagnosticCode::kTypeIsNotAFunction,
          std::vector<diagnostic::DiagnosticArg>{
              expression->getType()->getName()});
      m_context->reportError(err.get());
      return std::move(err);
    }
    return std::make_unique<BoundNewExpression>(std::move(expression),
                                                location);
  }

  auto err = std::make_unique<BoundErrorExpression>(
      location, diagnostic::DiagnosticCode::kUnexpectedExpression,
      std::vector<diagnostic::DiagnosticArg>{
          syntax::toString(inner_syntax->getKind()),
          "class name (e.g. new MyClass() or new MyClass)"});
  m_context->reportError(err.get());
  return std::move(err);
}

} // namespace binding
} // namespace flow_wing