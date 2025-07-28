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

#include "src/IR/irGen/statements/StatementGenerationStrategy/StatementGenerationStrategy.h"
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#include <llvm/IR/Value.h>
#pragma clang diagnostic pop

class CodeGenerationContext;
class BoundStatement;
class BoundFunctionDeclaration;
class IRCodeGenerator;

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
