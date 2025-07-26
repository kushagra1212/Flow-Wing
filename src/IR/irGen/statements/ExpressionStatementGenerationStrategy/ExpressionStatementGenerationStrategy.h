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


#ifndef __FLOWWING_EXPRESSION_STATEMENT_STRATEGY_H__
#define __FLOWWING_EXPRESSION_STATEMENT_STRATEGY_H__

#include "src/SemanticAnalyzer/BoundStatements/BoundExpressionStatement/BoundExpressionStatement.h"
#include "src/IR/irGen/statements/StatementGenerationStrategy/StatementGenerationStrategy.h"

class ExpressionStatementGenerationStrategy
    : public StatementGenerationStrategy {
public:
  ExpressionStatementGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateStatement(BoundStatement *statement) override;
  llvm::Value *generateGlobalStatement(BoundStatement *statement) override;
};

#endif //__FLOWWING_EXPRESSION_STATEMENT_STRATEGY_H__
