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

#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/IR/context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "src/IR/irGen/expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"
#include "src/IR/irGen/statements/ContainerDeclarationStatementGenerationStrategy/ContainerDeclarationStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/ObjectDeclarationStatementGenerationStrategy/ObjectDeclarationStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/StatementGenerationStrategy/StatementGenerationStrategy.h"

class VariableDeclarationStatementGenerationStrategy
    : public StatementGenerationStrategy {

public:
  VariableDeclarationStatementGenerationStrategy(
      CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *declareGlobal(BoundStatement *statement);
  llvm::Value *declareLocal(BoundStatement *statement);

  // Specialized for BoundVariableDeclaration

  bool canGenerateStatement(BoundStatement *statement);

  // Local Primitive Variable Declaration

  llvm::Value *handleTypedPrimitiveLocalVariableDeclaration(
      const std::string &variableName,
      const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue);

  llvm::Value *handleDynamicValuePrimitiveLocalVariableDeclare(
      const std::string &variableName, llvm::Value *rhsValue);

  llvm::Value *handlePrimitiveLocalVariableDeclaration(
      const std::string &variableName,
      const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue);

  llvm::Value *
  generateCommonStatement(BoundVariableDeclaration *variableDeclaration);

private:
  std::string _variableName;
  llvm::Value *_rhsValue = nullptr;
  int8_t m_isLHSDynamicValue = 0;
  SyntaxKindUtils::SyntaxKind _variableType;
  BoundVariableDeclaration *_variableDeclaration = nullptr;
  bool _isGlobal = false;

  llvm::Value *declare();
  void populateVariables(BoundStatement *statement,
                         BinderKindUtils::MemoryKind memoryKind =
                             BinderKindUtils::MemoryKind::None);
};
