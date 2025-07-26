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
#include <any>
#include <string>

#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundCallExpression/BoundCallExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"

#include "InterpreterUtils/InterpreterUtils.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundExpressionStatement/BoundExpressionStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundForStatement/BoundForStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundWhileStatement/BoundWhileStatement.h"
#include "src/SemanticAnalyzer/SemanticAnalyzer.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/utils/Utils.h"

class Interpreter {
private:
public:
  Interpreter(BoundGlobalScope *globalScope,
              FlowWing::DiagnosticHandler *diagnosticHandler);

  void execute(BoundBlockStatement *node);
  std::string getResult();

private:
  std::any last_value = nullptr;
  CompilationUnitSyntax *compilation_unit = nullptr;
  Interpreter *previous = nullptr;
  std::stack<std::unordered_map<std::string, BoundVariableDeclaration *>>
      variable_stack;
  std::stack<std::unordered_map<std::string, std::any>> value_stack;

  std::stack<std::unordered_map<std::string, BoundFunctionDeclaration *>>
      function_stack;
  std::stack<std::pair<SyntaxKindUtils::SyntaxKind, int>> return_type_stack;
  BoundGlobalScope *_globalScope = nullptr;
  std::unique_ptr<InterpreterUtils> _interpreterUtils;
  int break_count = 0, continue_count = 0, showResult = 1;

  void evaluateExpressionStatement(BoundExpressionStatement *node);
  void evaluateBlockStatement(BoundBlockStatement *node);
  void evaluateVariableDeclaration(BoundVariableDeclaration *node);
  void evaluateIfStatement(BoundIfStatement *node);
  void evaluateWhileStatement(BoundWhileStatement *node);
  void evaluateForStatement(BoundForStatement *node);
  void assignVariable(std::string name, std::any val);
  void evaluateStatement(BoundStatement *node);
  void declareVariable(std::string name, BoundVariableDeclaration *variable);
  void defineFunction(std::string name,
                      BoundFunctionDeclaration *functionDeclaration);

  BoundFunctionDeclaration *getFunction(std::string name);
  std::any getVariable(const std::string &name);
  template <typename T> T evaluateLiteralExpression(BoundExpression *node);
  template <typename T> T evaluateUnaryExpression(BoundExpression *node);
  template <typename T> T evaluateBinaryExpression(BoundExpression *node);
  template <typename T> T evaluateAssignmentExpression(BoundExpression *node);
  template <typename T> T evaluateVariableExpression(BoundExpression *node);
  template <typename T> T evaluateIndexExpression(BoundExpression *node);
  template <typename T> T evaluate(BoundExpression *node);

  std::any handleBuiltInFunction(BoundCallExpression *node);

  std::any unaryExpressionEvaluator(BoundUnaryExpression *unaryExpression,
                                    std::any operand);

  template <typename T>
  T binaryExpressionEvaluator(BoundBinaryExpression *binaryExpression, T left,
                              T right);
};