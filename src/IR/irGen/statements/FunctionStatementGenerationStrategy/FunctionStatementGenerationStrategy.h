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


#ifndef __FLOWWING_FUNCTION_STATEMENT_STRATEGY_H__
#define __FLOWWING_FUNCTION_STATEMENT_STRATEGY_H__

#include "../../../../SemanticAnalyzer/BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../Types/LLVMType/LLVMDynamicType/LLVMDynamicType.h"
#include "../../Types/LLVMType/LLVMObjectType/LLVMObjectType.h"
#include "../../Types/LLVMType/LLVMPrimitiveType/LLVMPrimitiveType.h"
#include "../../declaration/IRCodeGenerator/IRCodeGenerator.h"
#include "../../expressions/ContainerAssignmentExpressionGenerationStrategy/ContainerAssignmentExpressionGenerationStrategy.h"
#include "../../expressions/ObjectExpressionGenerationStrategy/ObjectExpressionGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class FunctionStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  FunctionStatementGenerationStrategy(CodeGenerationContext *context);
  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  llvm::Value *generateStatementOnFly(BoundFunctionDeclaration *node,
                                      std::vector<llvm::Value *> callArgs);

  void declareVariables(BoundStatement *statement);
  void declareVariables(BoundNode *statement);

  llvm::Value *generate(BoundStatement *statement,
                        std::vector<std::string> classParams = {},
                        llvm::Type *classType = nullptr,
                        std::vector<std::string> classVariables = {});

private:
  std::unique_ptr<IRCodeGenerator> _irCodeGenerator = nullptr;
};

#endif // __FLOWWING_VARIABLE_EXPRESSION_STRATEGY_H__
