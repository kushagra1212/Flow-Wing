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



#include "src/SemanticAnalyzer/DeclarationAnalyzer/DeclarationAnalyzer.hpp"
#include "src/common/Symbol/ScopedSymbolTable/ScopedSymbolTable.hpp"
#include "src/common/Symbol/Symbol.hpp"
#include "src/common/types/ClassType/ClassType.hpp"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"

namespace flow_wing {
void analysis::DeclarationAnalyzer::visit(syntax::ClassStatementSyntax *node) {
  auto *name_expr = static_cast<syntax::IdentifierExpressionSyntax *>(
      node->getClassNameIdentifierExpr().get());
  const auto &class_name = name_expr->getValue();

  std::shared_ptr<types::ClassType> parent_class_type = nullptr;
  if (node->getParentClassIdentifierExpr()) {
    auto &parent_name = static_cast<syntax::IdentifierExpressionSyntax *>(
                            node->getParentClassIdentifierExpr().get())
                            ->getValue();
    auto parent_sym = m_binder_context.getSymbolTable()->lookup(parent_name);
    if (parent_sym && parent_sym->getKind() == analysis::SymbolKind::kClass) {
      parent_class_type =
          std::dynamic_pointer_cast<types::ClassType>(parent_sym->getType());
    }
  }

  auto class_type =
      std::make_shared<types::ClassType>(class_name, parent_class_type);
  auto class_symbol = std::make_shared<analysis::Symbol>(
      class_name, analysis::SymbolKind::kClass, class_type);
  if (!m_binder_context.getSymbolTable()->define(class_symbol)) {
    m_binder_context.recordDuplicateClassDeclaration(class_name);
  }
}
} // namespace flow_wing