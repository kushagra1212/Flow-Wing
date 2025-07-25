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
#include "../../../../SemanticAnalyzer/BoundStatements/BoundSwitchStatement/BoundSwitchStatement.h"
#include "../../expressions/BinaryExpressionGenerationStrategy/BinaryExpressionGenerationStrategy.h"
#include "../StatementGenerationStrategy/StatementGenerationStrategy.h"

class SwitchStatementGenerationStrategy : public StatementGenerationStrategy {
public:
  SwitchStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;

  void
  populateSwitchStatementsBasicBlock(std::vector<llvm::BasicBlock *> &casesBB,
                                     const uint64_t &casesSize,
                                     llvm::Function *&function);

  void populateSwitchExpressionValue(llvm::Value *&expressionValue,
                                     BoundExpression *expression);
};
