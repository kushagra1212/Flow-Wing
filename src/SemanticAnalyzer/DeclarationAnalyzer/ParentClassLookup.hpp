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

#pragma once

#include "src/common/Symbol/ModuleSymbol.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/ModuleAccessExpressionSyntax/ModuleAccessExpressionSyntax.h"
#include <memory>
#include <string>

namespace flow_wing {
namespace analysis {

// The class after `extends`: `Base`, declared in this program, or
// `module::Base`, declared by a brought module (class Clicked extends
// js::Handler). Used by both passes that read a class statement, so they agree.
struct ParentClass {
  std::string name;               // as written, for diagnostics
  std::shared_ptr<Symbol> symbol; // null when there is no such name
};

inline ParentClass lookupParentClass(const ScopedSymbolTable &table,
                                     const syntax::ExpressionSyntax *expr) {
  if (expr->getKind() == syntax::NodeKind::kModuleAccessExpression) {
    const auto *access =
        static_cast<const syntax::ModuleAccessExpressionSyntax *>(expr);
    const auto &module_name =
        static_cast<const syntax::IdentifierExpressionSyntax *>(
            access->getModuleNameExpression().get())
            ->getValue();
    const auto &class_name =
        static_cast<const syntax::IdentifierExpressionSyntax *>(
            access->getMemberAccessExpression().get())
            ->getValue();

    ParentClass parent{module_name + "::" + class_name, nullptr};
    auto module = table.lookup(module_name);
    if (module && module->getKind() == SymbolKind::kModule) {
      parent.symbol = static_cast<const ModuleSymbol *>(module.get())
                          ->getModuleSymbolTable()
                          ->lookup(class_name);
    }
    return parent;
  }

  const auto &name =
      static_cast<const syntax::IdentifierExpressionSyntax *>(expr)->getValue();
  return {name, table.lookup(name)};
}

} // namespace analysis
} // namespace flow_wing
