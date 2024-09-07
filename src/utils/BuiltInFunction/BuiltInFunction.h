#ifndef __BUILT_IN_FUNCTION_H__
#define __BUILT_IN_FUNCTION_H__

#include "../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../bind/BoundTypeExpression/BoundTypeExpression.h"

namespace FW::BI::FUNCTION {

// Function Names

extern const std::string Int32;
extern const std::string Int8;
extern const std::string Decimal;
extern const std::string Decimal32;
extern const std::string String;
extern const std::string Bool;

extern const std::string Print;
extern const std::string Input;

}; // namespace FW::BI::FUNCTION
class BuiltInFunction {
  static std::vector<std::unique_ptr<BoundFunctionDeclaration>> _functions;

public:
  static void setupBuiltInFunctions();

  static auto isBuiltInFunction(const std::string &functionName) -> const bool;
  static auto getBuiltInFunction(const std::string &functionName)
      -> const std::unique_ptr<BoundFunctionDeclaration> &;

  inline static auto getBuiltInFunctions()
      -> const std::vector<std::unique_ptr<BoundFunctionDeclaration>> & {
    return _functions;
  }

  inline static auto getReturnType(const std::string &functionName)
      -> SyntaxKindUtils::SyntaxKind {
    if (functionName == FW::BI::FUNCTION::Int32)
      return SyntaxKindUtils::SyntaxKind::Int32Keyword;

    // TODO: One Day
    // if (functionName == FW::BI::FUNCTION::Int64)
    //   return SyntaxKindUtils::SyntaxKind::Int64Keyword;

    if (functionName == FW::BI::FUNCTION::Int8)
      return SyntaxKindUtils::SyntaxKind::Int8Keyword;

    if (functionName == FW::BI::FUNCTION::Decimal)
      return SyntaxKindUtils::SyntaxKind::DeciKeyword;

    if (functionName == FW::BI::FUNCTION::Decimal32)
      return SyntaxKindUtils::SyntaxKind::Deci32Keyword;

    if (functionName == FW::BI::FUNCTION::String)
      return SyntaxKindUtils::SyntaxKind::StrKeyword;

    if (functionName == FW::BI::FUNCTION::Bool)
      return SyntaxKindUtils::SyntaxKind::BoolKeyword;

    return SyntaxKindUtils::SyntaxKind::NthgKeyword;
  }
};

#endif // __BUILT_IN_FUNCTION_H__
