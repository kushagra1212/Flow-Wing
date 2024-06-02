#ifndef __BUILT_IN_FUNCTION_H__
#define __BUILT_IN_FUNCTION_H__

#include "../../bind/BoundFunctionDeclaration/BoundFunctionDeclaration.h"
#include "../../bind/BoundTypeExpression/BoundTypeExpression.h"
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
};

namespace FW::BI::FUNCTION {

// Function Names

extern const std::string Int32;
extern const std::string Decimal;
extern const std::string Decimal32;
extern const std::string String;
extern const std::string Bool;

extern const std::string Print;
extern const std::string Input;

}; // namespace FW::BI::FUNCTION

#endif // __BUILT_IN_FUNCTION_H__
