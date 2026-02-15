/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 */
#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace flow_wing {
namespace diagnostic {

using DiagnosticArg = std::variant<std::string, int, double, bool>;
using DiagnosticArgs = std::vector<flow_wing::diagnostic::DiagnosticArg>;

struct MessageTemplate {
  std::string message;
  std::string help;
  std::string note;
};

enum class DiagnosticCode : int16_t {
  kNone,

  // --- Source Loader Errors ---
  kUnableToOpenFile,

  // --- Lexical Errors ---
  kUnterminatedSingleQuote,
  kBadCharacterEscapeSequence,
  kNumberTooLargeForInt,
  kUnterminatedStringLiteral,
  kBadCharacterEscapeSequenceInStringLiteral,
  kBadCharacterInput,
  kUnterminatedTemplateStringLiteral,
  kUnexpectedCharacter,

  // --- Syntactic Errors ---
  kUnexpectedToken,
  kInvalidBracketedExpression,
  kReturnStatementOutsideOfFunction,
  kNoDefaultCaseInSwitchStatement,
  kMoreThanOneDefaultCaseInSwitchStatement,
  kNoCaseStatementInSwitchStatement,
  kContinueStatementOutsideOfLoop,
  kInvalidBreakStatementUsage,

  // --- Semantic Errors ---
  kUnexpectedTypeExpression,
  kUnexpectedExpression,
  kInValidTypeExpression,
  kInvalidAssignmentToUndeclaredVariable,
  kInvalidAssignmentToConstantVariable,
  kAssignmentToNonVariable,
  kAssignmentToNonLValue,
  kVariableNotFound,
  kVariableAlreadyDeclared,
  kFunctionNotFound,
  kFunctionAlreadyDeclared,
  kFunctionNameConflictsWithBuiltin,
  kIncorrectArgumentCount,
  kPassingMismatchedTypeToFunction,
  kPassingObjectToNonObjectParam,
  kPassingArrayToNonArrayParam,
  kArrayInitializerNotAllowedForDynamicType,
  kObjectInitializerNotAllowedForDynamicType,
  kPassingByReferenceWithAsKeywordIsNotAllowed,
  kArrayPassedInFunctionArgumentMismatch,
  kArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeButArrayDimensionMismatch,
  kArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeAndHavingSameDimensionButSizeMismatch,
  kVariablePassedAsAnArgumentToFunctionIsNotAnArray,
  kIndexingNonArrayVariable,
  kTypeOrClassNotFound,
  kTypeAlreadyDeclared,
  kCustomTypeNotFound,
  kDuplicateCustomTypeDeclaration,
  kDuplicateAttributeKeyInCustomType,
  kUnSupportedUnaryOperatorForClassType,
  kCanNotAssignObjectToDynamicType,
  kCanNotAssignNonDynamicSupertypeToDynamicVariable,
  kFunctionNameRequired,

  // Types
  kInvalidParameterType,
  kNthgCannotBeUsedAsParameterType,
  kExpectedNonNegativeIntegerForArrayDimension,

  // Expose Statement Errors
  kUnsupportedStatementInExposeStatement,

  // Function Errors
  kFunctionDeclarationDoesNotAllowDefaultParameterValues,
  // Function Parameter Errors
  kParameterAlreadyDeclared,

  // Conversion Errors ---
  kExpectedInt64Value,

  // --- Class-related Semantic Errors ---
  kClassAlreadyDeclared,
  kParentClassNotFound,
  kClassMissingSuperclass,
  kClassMissingInitializer,
  kMemberFunctionOfClassAlreadyDeclared,
  kSuperCallOutsideConstructor,
  kInvalidInitFunctionCall,

  // --- Module & Import Errors ---
  kModuleNotFound,
  kModuleAlreadyDeclared,
  kDuplicateModuleDeclaration,
  kCircularReference,
  kFileNotFound,
  kIdentifierNotFoundInFileOrModule,
  kUnsupportedExpressionOrStatementInModule,
  kImportModuleWithErrorsWarning,
  kMissingDefaultValueForOptionalParameter,

  // Variable Declaration Errors
  kInitializerExpressionTypeMismatch,
  kTooManyInitializerExpressions,
  kExpectedADefaultValueAfterTheFirstOptionalParameter,

  // Custom Type Errors
  kCustomTypeAlreadyDeclared,

  // Index Expression Errors
  kIndexingNonArrayTypeVariable,

  // Call Expression Errors
  kTypeIsNotAFunction,
  kFunctionArgumentCountMismatch,
  kFunctionArgumentTypeMismatch,

  // Member Access Expression Errors
  kMemberAccessOnNonObjectVariable,
  kMemberNotFoundInObject,

  // Ternary Expression Errors
  kIncompatibleTypesForTernaryExpression,

  // Unary Expression Errors
  kInvalidUnaryOperator,

  // Binary Expression Errors
  kInvalidBinaryOperationWithTypes,

  // Assignment Expression Errors
  kAssignmentExpressionTypeMismatch,
  kAssignmentExpressionCountMismatch,

  // For Statement Errors
  kTooManyDeclaratorsInVariableDeclaration,

  // For Loop Variable Declaration Errors
  kInvalidVariableDeclarationTypeForForLoopVariableDeclaration,
  kMultiTargetAssignmentNotAllowedForForLoopAssignmentExpression,
  kInvalidAssignmentExpressionTypeForForLoopAssignmentExpression,
  kInvalidUpperBoundTypeForForLoop,
  kInvalidStepTypeForForLoop,

  // Break Statement Errors
  kBreakStatementNotAllowedOutsideOfLoop,

  // Continue Statement Errors
  kContinueStatementNotAllowedOutsideOfLoop,

  // Return Statement Errors
  kReturnStatementNotInFunction,

  // Return Expression Errors
  kInvalidNumberOfReturnExpressions,

  // Return Expression Type Mismatch Errors
  kReturnExpressionTypeMismatch,

  // Switch Statement Errors
  kMultipleDefaultCaseStatements,
  kCaseExpressionTypeMismatch,

  // Class Statement Errors
  kParentClassIsNotAClass,
  kInvalidClassMemberStatement,
  kDuplicateMemberInClass,

  // Bring Statement Errors
  kFileContainsErrors,

  // Internal Errors
  kInternalIRGenerationError,

  // Constant Variable Errors
  kMissingInitializerExpression,
  kTooFewInitializerExpressions,

  // Container Expression Errors
  kContainerExpressionRankMismatch,

  // Array Indexing Errors
  kCannotIndexNonArrayType,

};

} // namespace diagnostic
} // namespace flow_wing
