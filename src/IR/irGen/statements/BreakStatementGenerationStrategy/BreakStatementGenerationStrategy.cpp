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


#include "BreakStatementGenerationStrategy.h"

BreakStatementGenerationStrategy::BreakStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *BreakStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {

  BoundBreakStatement *boundBreakStatement =
      static_cast<BoundBreakStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundBreakStatement->getLocation());

  _codeGenerationContext->incrementCount(
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));

  return nullptr;
}

llvm::Value *BreakStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {

  BoundBreakStatement *boundBreakStatement =
      static_cast<BoundBreakStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundBreakStatement->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Break statement cannot be used outside of a loop");

  return nullptr;
}