#pragma once

#include <cstdint>

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
  UnSupportedUnaryOperatorForClassType = 43,
  ParentClassNotFound = 44,
  ContinueStatementOutsideOfLoop = 45,
  DuplicateAttributeKeyInCustomType = 46,
  DuplicateCustomTypeDeclaration = 47,
  UnsupportedExpressionOrStatementInModule = 48,
  DuplicateModuleDeclaration = 49,
  ReturnStatementOutsideOfFunction = 50,
  NoDefaultCaseInSwitchStatement = 51,
  MoreThanOneDefaultCaseInSwitchStatement = 52,
  NoCaseStatementInSwitchStatement = 53,
  UnTerminatedSingleQuote = 54,
  BadCharacterEscapeSequence = 55,
  NumberTooLargeForInt = 56,
};

}
} // namespace FLOW_WING