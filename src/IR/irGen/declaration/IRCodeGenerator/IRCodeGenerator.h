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


#ifndef __FLOWWING_IR__CODE_GENERATOR_H__
#define __FLOWWING_IR__CODE_GENERATOR_H__

#include "src/IR/irGen/expressions/AssignmentExpressionGenerationStrategy/AssignmentExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/BinaryExpressionGenerationStrategy/BinaryExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/CallExpressionGenerationStrategy/CallExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/MultipleAssignmentExpressionGenerationStrategy/MultipleAssignmentExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/UnaryExpressionGenerationStrategy/UnaryExpressionGenerationStrategy.h"
#include "src/IR/irGen/statements/BringStatementGenerationStrategy/BringStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/ClassStatementGenerationStrategy/ClassStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/CustomTypeStatementGenerationStrategy/CustomTypeStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/MultipleVariableDeclarationStatementGenerationStrategy/MultipleVariableDeclarationStatementGenerationStrategy.h"
#include "src/IR/irGen/statements/VariableDeclarationStatementGenerationStrategy/VariableDeclarationStatementGenerationStrategy.h"
class IRCodeGenerator {
  std::unique_ptr<VariableDeclarationStatementGenerationStrategy>
      _variableDeclarationStatementGenerationStrategy;
  std::unique_ptr<MultipleVariableDeclarationStatementGenerationStrategy>
      _multipleVariableDeclarationStatementGenerationStrategy;

  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      _customTypeStatementGenerationStrategy;
  std::unique_ptr<ClassStatementGenerationStrategy>
      _classStatementGenerationStrategy;
  std::unique_ptr<CallExpressionGenerationStrategy>
      _callExpressionGenerationStrategy;
  std::unique_ptr<AssignmentExpressionGenerationStrategy>
      _assignmentExpressionGenerationStrategy;
  std::unique_ptr<BinaryExpressionGenerationStrategy>
      _binaryExpressionGenerationStrategy;
  std::unique_ptr<UnaryExpressionGenerationStrategy>
      _unaryExpressionGenerationStrategy;

  std::unique_ptr<MultipleAssignmentExpressionGenerationStrategy>
      _multipleAssignmentExpressionGenerationStrategy;

  void processChildForDeclaration(BoundNode *child, bool isGlobal);
  void processChildForCustomType(BoundNode *child);

public:
  IRCodeGenerator(CodeGenerationContext *context);
  void declareVariables(BoundNode *node, bool isGlobal);
  void declareCustomType(BoundNode *node);
  CodeGenerationContext *_codeGenerationContext;
};

#endif
