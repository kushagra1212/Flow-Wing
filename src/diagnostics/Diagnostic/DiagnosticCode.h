#pragma once

#include "../../utils/Colors.h"
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace FLOW_WING {
namespace DIAGNOSTIC {

enum class DiagnosticCode : int16_t {
  None = 0,
  PassingObjectToNonObjectParam = 1,
  PassingArrayToNonArrayParam = 2,
  PassingMismatchedTypeToFunction = 3,
  ArrayInitializerNotAllowedForDynamicType = 4,
  ObjectInitializerNotAllowedForDynamicType = 5,
  PassingByReferenceWithAsKeywordIsNotAllowed = 6,
  ArrayPassedInFunctionArgumentMismatch = 7,
  ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeButArrayDimensionMismatch =
      8,
  ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeAndHavingSameDimensionButSizeMismatch =
      9,
  VariablePassedAsAnArgumentToFunctionIsNotAnArray = 10,
  FunctionArgumentCountMismatch = 11,
  UnexpectedTypeExpression = 12,
  UnexpectedToken = 13,
  UnexpectedCharacter = 14,
  ModuleNotFound = 15,
  CircularReference = 16,
  InvalidAssignment = 17,
  InvalidAssignmentToUndeclaredVariable = 18,
  InvalidAssignmentToConstantVariable = 19,
  InvalidBracketedExpression = 20,
  SuperCallOutsideConstructor = 21,
  InvalidInitFunctionCall = 22,
  IncorrectArgumentCount = 23,
  ClassMissingSuperclass = 24,
  ClassMissingInitializer = 25,
  FunctionNotFound = 26,
  VariableNotFound = 27,
  IndexingNonArrayVariable = 28,
  InValidTypeExpression = 29,
  TypeOrClassNotFound = 30,
  FunctionAlreadyDeclared = 31,
  MemberFunctionOfClassAlreadyDeclared = 32,
  FunctionNameConflictsWithBuiltin = 33,
  MissingDefaultValueForOptionalParameter = 34,
  InvalidBreakStatementUsage = 35,
  FileNotFound = 36,
  IdentifierNotFoundInFileOrModule = 37,
  ModuleAlreadyDeclared = 38,
  VariableAlreadyDeclared = 39,
  TypeAlreadyDeclared = 40,
  ClassAlreadyDeclared = 41,
  ImportModuleWithErrorsWarning = 42,
  UnSupportedUnaryOperatorForClassType = 43
};
struct MessageTemplate {
  std::string message;
  std::string help;
  std::string note;
}; // namespace DIAGNOSTIC

using DiagnosticArg = std::variant<std::string, int, double, bool>;

std::string argToString(const DiagnosticArg &arg);

std::string formatMessage(std::string templateStr,
                          const std::vector<DiagnosticArg> &args,
                          const bool withHighlight = true);

std::string getErrorCode(const DiagnosticCode &code);

} // namespace DIAGNOSTIC
} // namespace FLOW_WING
