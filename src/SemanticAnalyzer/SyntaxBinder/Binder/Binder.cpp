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


#include "Binder.hpp"
#include "src/SemanticAnalyzer/BinderContext/BinderContext.hpp"
#include "src/SemanticAnalyzer/SyntaxBinder/CompilationUnitBinder/CompilationUnitBinder.hpp"
#include "src/compiler/CompilationContext/CompilationContext.h"

namespace flow_wing {
namespace analysis {

Binder::Binder(binding::BinderContext &binder_context)
    : m_binder_context(binder_context) {}

std::unique_ptr<binding::BoundCompilationUnit> Binder::bindRoot() {

  auto compilation_unit_binder =
      std::make_unique<binding::CompilationUnitBinder>(&m_binder_context);

  return compilation_unit_binder->bind(
      m_binder_context.getCompilationContext().getAst().get());
}

} // namespace analysis
} // namespace flow_wing