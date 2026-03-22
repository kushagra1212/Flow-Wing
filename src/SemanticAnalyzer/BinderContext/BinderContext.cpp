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

#include "BinderContext.hpp"
#include "src/SemanticAnalyzer/BoundStatements/BoundErrorStatement/BoundErrorStatement.hpp"
#include "src/SemanticAnalyzer/TypeResolver/TypeResolver.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/types/Type.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/compiler/diagnostics/DiagnosticFactory.h"
#include <cassert>

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

void BinderContext::reportError(
    binding::BoundErrorExpression *error_expression) {
  reportError(error_expression->getCode(), error_expression->getArgs(),
              error_expression->getSourceLocation());
}

void BinderContext::reportError(binding::BoundErrorStatement *error_statement) {
  reportError(error_statement->getCode(), error_statement->getArgs(),
              error_statement->getSourceLocation());
}

void BinderContext::switchSymbolTable(
    std::shared_ptr<analysis::ScopedSymbolTable> symbol_table) {
  m_symbol_table = symbol_table;
}

void BinderContext::setCurrentClassType(
    std::shared_ptr<types::Type> class_type) {
  m_current_class_type = std::move(class_type);
}

std::shared_ptr<types::Type> BinderContext::getCurrentClassType() const {
  return m_current_class_type;
}

void BinderContext::pushExpectedType(std::shared_ptr<types::Type> type) {
  m_expected_type_stack.push_back(std::move(type));
}

void BinderContext::popExpectedType() {
  assert(!m_expected_type_stack.empty() &&
         "popExpectedType without matching push");
  m_expected_type_stack.pop_back();
}

std::shared_ptr<types::Type> BinderContext::peekExpectedType() const {
  if (m_expected_type_stack.empty())
    return nullptr;
  return m_expected_type_stack.back();
}

void BinderContext::recordDuplicateClassDeclaration(
    const std::string &class_name) {
  m_duplicate_class_declarations.insert(class_name);
}

bool BinderContext::isDuplicateClassDeclaration(
    const std::string &class_name) const {
  return m_duplicate_class_declarations.find(class_name) !=
         m_duplicate_class_declarations.end();
}

} // namespace binding
} // namespace flow_wing