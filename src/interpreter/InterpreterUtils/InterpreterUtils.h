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


#ifndef INTERPRETERUTILS_H
#define INTERPRETERUTILS_H
#include <any>

#include "../../SemanticAnalyzer/BinderKindUtils.h"
#include "../../SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../../common/Common.h"
#include "../../diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "../../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "InterpreterConversions/InterpreterConversion.h"

class InterpreterUtils {
private:
  DiagnosticUtils::SourceLocation _currentSourceLocation;
  FlowWing::DiagnosticHandler *_diagnosticHandler = nullptr;

public:
  InterpreterUtils(FlowWing::DiagnosticHandler *diagnosticHandler);

  void setCurrentSourceLocation(DiagnosticUtils::SourceLocation sourceLocation);
  DiagnosticUtils::SourceLocation getCurrentSourceLocation();
  FlowWing::DiagnosticHandler *getDiagnosticHandler();
  void logError(const std::string message);

  std::any
  getResultFromBinaryOperationOnString(std::string lhsValue,
                                       std::string rhsValue,
                                       BoundBinaryExpression *binaryExpression);
  std::any
  getResultFromBinaryOperationOnDouble(double lhsValue, double rhsValue,
                                       BoundBinaryExpression *binaryExpression);

  std::any
  getResultFromBinaryOperationOnInt(int lhsValue, int rhsValue,
                                    BoundBinaryExpression *binaryExpression);

  std::any
  getResultFromBinaryOperationOnBool(bool lhsValue, bool rhsValue,
                                     BoundBinaryExpression *binaryExpression);

  template <typename T>
  std::any getResultFromUnaryExpressionEvaluatorHandler(
      BinderKindUtils::BoundUnaryOperatorKind op, T operand);

  // Int (unary)
  std::any getResultFromUnaryExpressionEvaluatorHandlerForInt(
      BinderKindUtils::BoundUnaryOperatorKind op, int operand);

  // Double (unary)
  std::any getResultFromUnaryExpressionEvaluatorHandlerForDouble(
      BinderKindUtils::BoundUnaryOperatorKind op, double operand);

  // Bool (unary)
  std::any getResultFromUnaryExpressionEvaluatorHandlerForBool(
      BinderKindUtils::BoundUnaryOperatorKind op, bool operand);
  // String (unary)
  std::any getResultFromUnaryExpressionEvaluatorHandlerForString(
      BinderKindUtils::BoundUnaryOperatorKind op, std::string operand);
};

#endif // INTERPRETERUTILS_H