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