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


#include "BinderContext.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticFactory.h"

namespace flow_wing {
namespace binding {

BinderContext::BinderContext(CompilationContext &context)
    : m_context(context),
      m_type_resolver(std::make_unique<analysis::TypeResolver>(this)),
      m_symbol_table(std::make_unique<analysis::ScopedSymbolTable>()) {}

BinderContext::~BinderContext() = default;

const CompilationContext &BinderContext::getCompilationContext() const {

  return m_context;
}

const std::shared_ptr<analysis::ScopedSymbolTable> &
BinderContext::getSymbolTable() const {
  return m_symbol_table;
}

const std::unique_ptr<analysis::TypeResolver> &
BinderContext::getTypeResolver() const {
  return m_type_resolver;
}

void BinderContext::reportError(
    flow_wing::diagnostic::DiagnosticCode code,
    const std::vector<flow_wing::diagnostic::DiagnosticArg> &args,
    const flow_wing::diagnostic::SourceLocation &location) {

  m_context.getDiagnostics()->report(
      flow_wing::diagnostic::DiagnosticFactory::create(
          code, args, location, flow_wing::diagnostic::DiagnosticLevel::kError,
          flow_wing::diagnostic::DiagnosticType::kSemantic));
}

void BinderContext::switchSymbolTable(
    std::shared_ptr<analysis::ScopedSymbolTable> symbol_table) {
  m_symbol_table = symbol_table;
}

} // namespace binding
} // namespace flow_wing