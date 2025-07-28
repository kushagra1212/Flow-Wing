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

#include "ModuleStatementGenerationStrategy.h"
#include <memory>

ModuleStatementGenerationStrategy::ModuleStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}
llvm::Value *ModuleStatementGenerationStrategy::generateStatement(
    [[maybe_unused]] BoundStatement *statement) {
  return nullptr;
}

llvm::Value *ModuleStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  BoundModuleStatement *boundModuleStatement =
      static_cast<BoundModuleStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundModuleStatement->getLocation());

  for (auto &stat : boundModuleStatement->getStatementsRef()) {
    switch (stat->getKind()) {
    case BinderKindUtils::BoundNodeKind::VariableDeclaration: {
      std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
          variableDeclarationStatementGenerationStrategy =
              std::make_unique<VariableDeclarationStatementGenerationStrategy>(
                  _codeGenerationContext);
      BoundVariableDeclaration *varDec =
          static_cast<BoundVariableDeclaration *>(stat);
      variableDeclarationStatementGenerationStrategy->generateGlobalStatement(
          varDec);

      break;
    }

    case BinderKindUtils::BoundNodeKind::CallExpression: {

      std::unique_ptr<CallExpressionGenerationStrategy>
          callExpressionGenerationStrategy =
              std::make_unique<CallExpressionGenerationStrategy>(
                  _codeGenerationContext);

      callExpressionGenerationStrategy->generateGlobalExpression(
          static_cast<BoundCallExpression *>(stat));
      break;
    }

    default: {
      break;
    }
    }
  }

  return nullptr;
}

llvm::Value *
ModuleStatementGenerationStrategy::declare(BoundStatement *statement) {

  BoundModuleStatement *boundModuleStatement =
      static_cast<BoundModuleStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundModuleStatement->getLocation());

  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (size_t i = 0;
       i < boundModuleStatement->getFunctionStatementsRef().size(); i++) {
    BoundFunctionDeclaration *fd = static_cast<BoundFunctionDeclaration *>(
        boundModuleStatement->getFunctionStatementsRef()[i].get());
    if (fd->isOnlyDeclared())
      functionDeclarationGenerationStrategy->generate(fd);
  }

  return nullptr;
}