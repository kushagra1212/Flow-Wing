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

#include "MultipleVariableDeclarationBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundMultipleVariableDeclaration/BoundMultipleVariableDeclaration.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "src/syntax/statements/MultipleVariableDeclarationSyntax/MultipleVariableDeclarationSyntax.h"
#include <memory>

std::unique_ptr<BoundStatement>
MultipleVariableDeclarationBinder::bindStatement(SyntaxBinderContext *ctx,
                                                 StatementSyntax *statement) {

  MultipleVariableDeclarationSyntax *multipleVariableDeclaration =
      static_cast<MultipleVariableDeclarationSyntax *>(statement);

  std::unique_ptr<BoundMultipleVariableDeclaration>
      boundMultipleVariableDeclaration =
          std::make_unique<BoundMultipleVariableDeclaration>(
              multipleVariableDeclaration->getSourceLocation());

  for (auto &variableDeclaration :
       multipleVariableDeclaration->getVariableDeclarationListRef()) {

    std::unique_ptr<BoundVariableDeclaration> boundVarDec(
        static_cast<BoundVariableDeclaration *>(
            StatementBinderFactory::create(variableDeclaration->getKind())
                ->bindStatement(ctx, variableDeclaration.get())
                .release()));

    boundMultipleVariableDeclaration->addVariableDeclaration(
        std::move(boundVarDec));
  }

  auto firstVariableDeclaration =
      boundMultipleVariableDeclaration->getVariableDeclarationListRef()[0]
          .get();

  for (size_t i = 1;
       i <
       boundMultipleVariableDeclaration->getVariableDeclarationListRef().size();
       i++) {
    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setIsConst(firstVariableDeclaration->isConst());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setHasAsKeyword(firstVariableDeclaration->getHasAsKeyword());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setHasInOutKeyword(firstVariableDeclaration->getHasInOutKeyword());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setMemoryKind(firstVariableDeclaration->getMemoryKind());

    boundMultipleVariableDeclaration->getVariableDeclarationListRef()[i]
        ->setIsExposed(firstVariableDeclaration->isExposed());
  }

  return std::move(boundMultipleVariableDeclaration);
}