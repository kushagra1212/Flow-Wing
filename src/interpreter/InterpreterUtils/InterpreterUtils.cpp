#include "InterpreterUtils.h"

InterpreterUtils::InterpreterUtils(DiagnosticHandler *diagnosticHandler) {
  this->_diagnosticHandler = diagnosticHandler;
}

DiagnosticHandler *InterpreterUtils::getDiagnosticHandler() {
  return this->_diagnosticHandler;
}

void InterpreterUtils::setCurrentSourceLocation(
    DiagnosticUtils::SourceLocation sourceLocation) {
  this->_currentSourceLocation = sourceLocation;
}
void InterpreterUtils::logError(const std::string message) {
  this->_diagnosticHandler->addDiagnostic(
      Diagnostic(message, DiagnosticUtils::DiagnosticLevel::Error,
                 DiagnosticUtils::DiagnosticType::Runtime,
                 this->getCurrentSourceLocation()));
}
DiagnosticUtils::SourceLocation InterpreterUtils::getCurrentSourceLocation() {
  return this->_currentSourceLocation;
}

std::any InterpreterUtils::getResultFromBinaryOperationOnString(
    std::string lhsValue, std::string rhsValue,
    BoundBinaryExpression *binaryExpression) {

  this->setCurrentSourceLocation(binaryExpression->getLocation());

  std::any result = nullptr;

  std::string errorMessage = "";

  std::string lhsStr = lhsValue;
  std::string rhsStr = rhsValue;

  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {

    return result = lhsValue + rhsValue;
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return result = lhsValue == rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return result = lhsValue != rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return result = lhsValue < rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    return result = lhsValue <= rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return result = lhsValue > rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return result = lhsValue >= rhsValue;
    break;

  // Add more cases for other binary operators
  default: {
    errorMessage = "Unsupported binary operator for string type " + lhsStr +
                   " and " + rhsStr;
    break;
  }
  }

  this->logError(errorMessage);

  return result;
}

std::any InterpreterUtils::getResultFromBinaryOperationOnDouble(
    double lhsValue, double rhsValue, BoundBinaryExpression *binaryExpression) {
  this->setCurrentSourceLocation(binaryExpression->getLocation());
  std::any result = nullptr;
  std::string errorMessage = "";
  std::string lhsStr =
      InterpreterConversion::explicitConvertDoubleToString(lhsValue);
  std::string rhsStr =
      InterpreterConversion::explicitConvertDoubleToString(rhsValue);
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
    return lhsValue + rhsValue;
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return lhsValue - rhsValue;
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return lhsValue * rhsValue;
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {
    // Check if rhsValue is zero

    if (!rhsValue) {
      std::string errorMessage =
          "Division by zero of " + lhsStr + " and " + rhsStr;

      this->logError(errorMessage);
      return result;
    }

    return lhsValue / rhsValue;
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    errorMessage =
        "Modulus is not supported for double type " + lhsStr + " and " + rhsStr;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    errorMessage = "Bitwise And is not supported for double type " + lhsStr +
                   " and " + rhsStr;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    errorMessage = "Bitwise Or is not supported for double type " + lhsStr +
                   " and " + rhsStr;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    errorMessage = "Bitwise Xor is not supported for double type " + lhsStr +
                   " and " + rhsStr;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    errorMessage = "Logical And is not supported for double type " + lhsStr +
                   " and " + rhsStr;

    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    errorMessage = "Logical Or is not supported for double type " + lhsStr +
                   " and " + rhsStr;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return lhsValue == rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return lhsValue != rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return lhsValue < rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    return lhsValue <= rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return lhsValue > rhsValue;
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return lhsValue >= rhsValue;
    break;

  // Add more cases for other binary operators
  default: {

    // write the brief error message

    errorMessage = "Unsupported binary operator for double type" + lhsStr +
                   " and " + rhsStr;

    break;
  }
  }
  this->logError(errorMessage);
  return result;
}

std::any InterpreterUtils::getResultFromBinaryOperationOnInt(
    int lhsValue, int rhsValue, BoundBinaryExpression *binaryExpression) {
  this->setCurrentSourceLocation(binaryExpression->getLocation());
  std::any result = nullptr;

  std::string errorMessage = "";

  std::string lhsStr =
      InterpreterConversion::explicitConvertIntToString(lhsValue);

  std::string rhsStr =
      InterpreterConversion::explicitConvertIntToString(rhsValue);

  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {
    return lhsValue + rhsValue;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return lhsValue - rhsValue;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return lhsValue * rhsValue;
  case BinderKindUtils::BoundBinaryOperatorKind::IntegerDivision: {

    // Check if rhsValue is zero
    if (!rhsValue) {

      std::string errorMessage =
          "Division by zero of " + lhsStr + " and " + rhsStr;

      this->logError(errorMessage);

      return result;
    }
    return InterpreterConversion::explicitConvertAnyToInt(lhsValue) /
           InterpreterConversion::explicitConvertAnyToInt(rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    // Check if rhsValue is zero
    if (!rhsValue) {

      std::string errorMessage =
          "Division by zero of " + lhsStr + " and " + rhsStr;

      this->logError(errorMessage);

      return result;
    }
    return (double)lhsValue / rhsValue;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    return lhsValue % rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return lhsValue & rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return lhsValue | rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return lhsValue ^ rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return InterpreterConversion::explicitConvertIntToBool(lhsValue) &&
           InterpreterConversion::explicitConvertIntToBool(rhsValue);

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return InterpreterConversion::explicitConvertIntToBool(lhsValue) ||
           InterpreterConversion::explicitConvertIntToBool(rhsValue);

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return lhsValue == rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return lhsValue != rhsValue;
  case BinderKindUtils::BoundBinaryOperatorKind::Less: {
    return lhsValue < rhsValue;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {
    return lhsValue <= rhsValue;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return lhsValue > rhsValue;
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:
    return lhsValue >= rhsValue;
  default: {

    errorMessage =
        "Unsupported binary operator for int type " + lhsStr + " and " + rhsStr;
    break;
  }
  }

  this->logError(errorMessage);
  return result;
}

std::any InterpreterUtils::getResultFromBinaryOperationOnBool(
    bool lhsValue, bool rhsValue, BoundBinaryExpression *binaryExpression) {
  std::any result = nullptr;
  std::string errorMessage = "";

  std::string lhsStr =
      InterpreterConversion::explicitConvertBoolToString(lhsValue);

  std::string rhsStr =
      InterpreterConversion::explicitConvertBoolToString(rhsValue);

  this->setCurrentSourceLocation(binaryExpression->getLocation());
  this->setCurrentSourceLocation(binaryExpression->getLocation());

  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return InterpreterConversion::explicitConvertAnyToBool(
        this->getResultFromBinaryOperationOnInt(
            InterpreterConversion::explicitConvertBoolToInt(lhsValue),
            InterpreterConversion::explicitConvertBoolToInt(rhsValue),
            binaryExpression));

  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    if (!rhsValue) {

      std::string errorMessage =
          "Division by zero of " + lhsStr + " and " + rhsStr;

      this->logError(errorMessage);
      return result;
    }

    return InterpreterConversion::explicitConvertAnyToBool(lhsValue / rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return lhsValue && rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return lhsValue || rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return lhsValue == rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return lhsValue != rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return lhsValue < rhsValue;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    return lhsValue <= rhsValue;

  case BinderKindUtils ::BoundBinaryOperatorKind::Greater:
    return lhsValue > rhsValue;

  case BinderKindUtils ::BoundBinaryOperatorKind::GreaterOrEquals:

    return lhsValue >= rhsValue;

  // Add more cases for other binary operators
  default:

    errorMessage = "Unsupported binary operator for bool type " + lhsStr +
                   " and " + rhsStr;

    break;
  }
  this->logError(errorMessage);

  return result;
}
template <typename T>
std::any InterpreterUtils::getResultFromUnaryExpressionEvaluatorHandler(
    BinderKindUtils::BoundUnaryOperatorKind op, T operand) {

  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
    return operand;
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {

    return -1 * operand;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return !InterpreterConversion::explicitConvertAnyToBool(operand);
  default:
    return operand;
  }
}
// Int (unary)
std::any InterpreterUtils::getResultFromUnaryExpressionEvaluatorHandlerForInt(
    BinderKindUtils::BoundUnaryOperatorKind op, int operand) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return getResultFromUnaryExpressionEvaluatorHandler<int>(op, operand);
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
    return ~(operand);
  default:

    this->logError("Unexpected unary operator" +
                   BinderKindUtils::to_string(op) + " for int");
    return operand;
  }
}
// Double (unary)
std::any
InterpreterUtils::getResultFromUnaryExpressionEvaluatorHandlerForDouble(
    BinderKindUtils::BoundUnaryOperatorKind op, double operand) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
  case BinderKindUtils::BoundUnaryOperatorKind::Negation:
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return getResultFromUnaryExpressionEvaluatorHandler<double>(op, operand);
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
    return ~InterpreterConversion::explicitConvertDoubleToInt(operand);
  default:

    this->logError("Unexpected unary operator" +
                   BinderKindUtils::to_string(op) + " for double");

    return operand;
  }
}

// Bool (unary)
std::any InterpreterUtils::getResultFromUnaryExpressionEvaluatorHandlerForBool(
    BinderKindUtils::BoundUnaryOperatorKind op, bool operand) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity:
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation:
    return getResultFromUnaryExpressionEvaluatorHandler<bool>(op, operand);
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {
    this->logError("Unexpected unary operator" +
                   BinderKindUtils::to_string(op) + " for bool");

    return operand;
  }
  default:

    this->logError("Unexpected unary operator");

    return operand;
  }
}

// String (unary)
std::any
InterpreterUtils::getResultFromUnaryExpressionEvaluatorHandlerForString(
    BinderKindUtils::BoundUnaryOperatorKind op, std::string operand) {
  switch (op) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {
    return operand;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    return !InterpreterConversion::explicitConvertAnyToBool(operand);
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation:
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {
    this->logError("Unexpected unary operator" +
                   BinderKindUtils::to_string(op) + " for String");

    return operand;
  }
  default:

    this->logError("Unexpected unary operator");

    return operand;
  }
}
