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

  auto create = [](std::string funName, SyntaxKindUtils::SyntaxKind rt,
                   bool isVariadic = true) {
    std::unique_ptr<BoundFunctionDeclaration> func =
        std::make_unique<BoundFunctionDeclaration>(
            DiagnosticUtils::SourceLocation(), false);
    func->setFunctionName(funName);
    func->addReturnExpr(std::move(std::make_unique<BoundTypeExpression>(
        DiagnosticUtils::SourceLocation(), rt)));

    if (!isVariadic) {
      std::unique_ptr<BoundVariableDeclaration> varDec =
          std::make_unique<BoundVariableDeclaration>(
              DiagnosticUtils::SourceLocation(), "par", false, false);

      varDec->setTypeExpression(std::make_unique<BoundTypeExpression>(
          DiagnosticUtils::SourceLocation(),
          SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE));

      func->addParameter(std::move(varDec));
    }

    func->setIsVariadicFunction(isVariadic);
    _functions.push_back(std::move(func));
  };

  create(FW::BI::FUNCTION::Int32, SyntaxKindUtils::SyntaxKind::Int32Keyword,
         false);

  // Int8
  create(FW::BI::FUNCTION::Int8, SyntaxKindUtils::SyntaxKind::Int8Keyword,
         false);

  // Decimal

  create(FW::BI::FUNCTION::Decimal, SyntaxKindUtils::SyntaxKind::DeciKeyword,
         false);

  // Decimal32

  create(FW::BI::FUNCTION::Decimal32,
         SyntaxKindUtils::SyntaxKind::Deci32Keyword, false);

  // String

  create(FW::BI::FUNCTION::String, SyntaxKindUtils::SyntaxKind::StrKeyword,
         false);

  // Bool

  create(FW::BI::FUNCTION::Bool, SyntaxKindUtils::SyntaxKind::BoolKeyword,
         false);

  // Input

  create(FW::BI::FUNCTION::Input, SyntaxKindUtils::SyntaxKind::StrKeyword,
         false);

  // Print

  create(FW::BI::FUNCTION::Print, SyntaxKindUtils::SyntaxKind::NthgKeyword);
}

namespace FW::BI::FUNCTION {

// Function Names

const std::string Int32 = "Int32";
const std::string Int8 = "Int8";
const std::string Decimal = "Decimal";
const std::string Decimal32 = "Decimal32";
const std::string String = "String";
const std::string Bool = "Bool";
const std::string Print = "print";
const std::string Input = "input";

}; // namespace FW::BI::FUNCTION