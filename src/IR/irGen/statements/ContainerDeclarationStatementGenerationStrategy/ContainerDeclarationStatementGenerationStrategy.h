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


#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundBracketedExpression/BoundBracketedExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundArrayTypeExpression/BoundArrayTypeExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundContainerStatement/BoundContainerStatement.h"
#include "src/IR/irGen/statements/StatementGenerationStrategy/StatementGenerationStrategy.h"

class ContainerDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {

public:
  // public methods
  ContainerDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declareLocal(BoundStatement *statement);
  llvm::Value *declareGlobal(BoundStatement *statement);

private:
  // private members
  std::vector<uint64_t> _actualSizes;
  llvm::Type *_elementType = nullptr;
  std::string _containerName;

  BoundExpression *_initializer;
  BinderKindUtils::MemoryKind _memoryKind;
  BoundArrayTypeExpression *_arrayTypeExpression;
  BoundVariableDeclaration *_variableDeclExpr;

  // private methods
  void calcActualContainerSize(BoundArrayTypeExpression *arrayTypeExpression);
  void initialize(BoundStatement *statement,
                  BinderKindUtils::MemoryKind memoryKind =
                      BinderKindUtils::MemoryKind::None);
  llvm::Value *declare();
  llvm::Value *assignExpression();
};
