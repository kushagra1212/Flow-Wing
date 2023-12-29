#include "BuiltInFunction.h"

auto BuiltInFunction::isBuiltInFunction(const std::string &functionName)
    -> const bool {
  for (const auto &function : _functions) {
    if (function->getFunctionNameRef() == functionName) {
      return true;
    }
  }
  return false;
}

auto BuiltInFunction::getBuiltInFunction(const std::string &functionName)
    -> const std::unique_ptr<BoundFunctionDeclaration> & {
  for (const auto &function : _functions) {
    if (function->getFunctionNameRef() == functionName) {
      return function;
    }
  }
  return _functions[0];
}

std::vector<std::unique_ptr<BoundFunctionDeclaration>>
    BuiltInFunction::_functions = {};

void BuiltInFunction::setupBuiltInFunctions() {

  std::any par = ("value");

  // Int32

  std::unique_ptr<BoundFunctionDeclaration> Int32Func =
      std::make_unique<BoundFunctionDeclaration>(
          DiagnosticUtils::SourceLocation());
  Int32Func->setFunctionName(FW::BI::FUNCTION::Int32);
  Int32Func->setReturnType(Utils::INT32);
  Int32Func->addParameter(std::make_unique<BoundVariableExpression>(
      DiagnosticUtils::SourceLocation(),
      std::make_unique<BoundLiteralExpression<std::any>>(
          DiagnosticUtils::SourceLocation(), par),
      false, Utils::type::UNKNOWN));
  _functions.push_back(std::move(Int32Func));

  // Decimal

  std::unique_ptr<BoundFunctionDeclaration> DecimalFunc =
      std::make_unique<BoundFunctionDeclaration>(
          DiagnosticUtils::SourceLocation());
  DecimalFunc->setFunctionName(FW::BI::FUNCTION::Decimal);
  DecimalFunc->setReturnType(Utils::DECIMAL);
  DecimalFunc->addParameter(std::make_unique<BoundVariableExpression>(
      DiagnosticUtils::SourceLocation(),
      std::make_unique<BoundLiteralExpression<std::any>>(
          DiagnosticUtils::SourceLocation(), par),
      false, Utils::type::UNKNOWN));
  _functions.push_back(std::move(DecimalFunc));

  // String

  std::unique_ptr<BoundFunctionDeclaration> StringFunc =
      std::make_unique<BoundFunctionDeclaration>(
          DiagnosticUtils::SourceLocation());
  StringFunc->setFunctionName(FW::BI::FUNCTION::String);
  StringFunc->setReturnType(Utils::STRING);
  StringFunc->addParameter(std::make_unique<BoundVariableExpression>(
      DiagnosticUtils::SourceLocation(),
      std::make_unique<BoundLiteralExpression<std::any>>(
          DiagnosticUtils::SourceLocation(), par),
      false, Utils::type::UNKNOWN));
  _functions.push_back(std::move(StringFunc));

  // Bool

  std::unique_ptr<BoundFunctionDeclaration> BoolFunc =
      std::make_unique<BoundFunctionDeclaration>(
          DiagnosticUtils::SourceLocation());
  BoolFunc->setFunctionName(FW::BI::FUNCTION::Bool);
  BoolFunc->setReturnType(Utils::BOOL);
  BoolFunc->addParameter(std::make_unique<BoundVariableExpression>(
      DiagnosticUtils::SourceLocation(),
      std::make_unique<BoundLiteralExpression<std::any>>(
          DiagnosticUtils::SourceLocation(), par),
      false, Utils::type::UNKNOWN));
  _functions.push_back(std::move(BoolFunc));

  // Input

  std::unique_ptr<BoundFunctionDeclaration> InputFunc =
      std::make_unique<BoundFunctionDeclaration>(
          DiagnosticUtils::SourceLocation());
  InputFunc->setFunctionName(FW::BI::FUNCTION::Input);
  InputFunc->setReturnType(Utils::STRING);
  InputFunc->addParameter(std::make_unique<BoundVariableExpression>(
      DiagnosticUtils::SourceLocation(),
      std::make_unique<BoundLiteralExpression<std::any>>(
          DiagnosticUtils::SourceLocation(), par),
      false, Utils::type::UNKNOWN));
  _functions.push_back(std::move(InputFunc));

  // Print

  std::unique_ptr<BoundFunctionDeclaration> PrintFunc =
      std::make_unique<BoundFunctionDeclaration>(
          DiagnosticUtils::SourceLocation());
  PrintFunc->setFunctionName(FW::BI::FUNCTION::Print);
  PrintFunc->setReturnType(Utils::NOTHING);
  PrintFunc->addParameter(std::make_unique<BoundVariableExpression>(
      DiagnosticUtils::SourceLocation(),
      std::make_unique<BoundLiteralExpression<std::any>>(
          DiagnosticUtils::SourceLocation(), par),
      false, Utils::type::UNKNOWN));
  _functions.push_back(std::move(PrintFunc));
}

namespace FW::BI::FUNCTION {

// Function Names

const std::string Int32 = "Int32";
const std::string Decimal = "Decimal";
const std::string String = "String";
const std::string Bool = "Bool";
const std::string Print = "print";
const std::string Input = "input";

}; // namespace FW::BI::FUNCTION