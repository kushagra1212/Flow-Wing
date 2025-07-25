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


#include "Diagnostic.h"
#include "DiagnosticCodeData.h"

Diagnostic::Diagnostic(const std::string &message,
                       DiagnosticUtils::DiagnosticLevel level,
                       DiagnosticUtils::DiagnosticType type,
                       const DiagnosticUtils::SourceLocation &location,
                       const FLOW_WING::DIAGNOSTIC::DiagnosticCode &code)
    : _message(message), _level(level), _type(type), _location(location),
      _messageTemplate({message, "", ""}), _code(code) {}

Diagnostic::Diagnostic(
    DiagnosticUtils::DiagnosticLevel level,
    DiagnosticUtils::DiagnosticType type,
    const std::vector<FLOW_WING::DIAGNOSTIC::DiagnosticArg> &args,
    const DiagnosticUtils::SourceLocation &location,
    const FLOW_WING::DIAGNOSTIC::DiagnosticCode &code)
    : _level(level), _type(type), _location(location), _code(code) {
  _messageTemplate = messageTemplate.at(code);
  _message =
      FLOW_WING::DIAGNOSTIC::formatMessage(_messageTemplate.message, args);
  _help = FLOW_WING::DIAGNOSTIC::formatMessage(_messageTemplate.help, args);
  _note = FLOW_WING::DIAGNOSTIC::formatMessage(_messageTemplate.note, args);
}

const FLOW_WING::DIAGNOSTIC::MessageTemplate &
Diagnostic::getMessageTemplate() const {
  return _messageTemplate;
}

const std::string &Diagnostic::getMessage() const { return _message; }

DiagnosticUtils::DiagnosticLevel Diagnostic::getLevel() const { return _level; }

DiagnosticUtils::DiagnosticType Diagnostic::getType() const { return _type; }

const DiagnosticUtils::SourceLocation &Diagnostic::getLocation() const {
  return _location;
}

const FLOW_WING::DIAGNOSTIC::DiagnosticCode &Diagnostic::getCode() const {
  return _code;
}

const std::string &Diagnostic::getHelp() const { return _help; }

const std::string &Diagnostic::getNote() const { return _note; }

std::unordered_map<FLOW_WING::DIAGNOSTIC::DiagnosticCode,
                   FLOW_WING::DIAGNOSTIC::MessageTemplate>
    Diagnostic::messageTemplate = {
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::PassingObjectToNonObjectParam),
         {"The function '{0}' does not expect an Object literal here. It "
          "expected a parameter of type '{1}'.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::PassingArrayToNonArrayParam),
         {"The function '{0}' does not expect an Array literal here. It "
          "expected a parameter of type '{1}'.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              PassingMismatchedTypeToFunction),
         {"The function '{0}' expects a parameter of type '{1}' but found a "
          "parameter of type '{2}'. Please pass a parameter of type '{1}'.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ArrayInitializerNotAllowedForDynamicType),
         {"The Dynamic type does not support array initializer for variable "
          "'{0}'.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ObjectInitializerNotAllowedForDynamicType),
         {"The Dynamic type does not support object initializer for variable "
          "'{0}'.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              PassingByReferenceWithAsKeywordIsNotAllowed),
         {"The keywords 'inout' and 'as' are mutually exclusive and cannot "
          "be "
          "used on the same parameter '{0}'.",
          R"(To fix this, please choose one:
  1. For pass-by-reference, remove the 'as' keyword: 'inout {0}: {1}'
  2. For type conversion, remove the 'inout' keyword: '{0}: as {1}')",
          R"('inout' specifies that the parameter is passed by reference, allowing the original variable to be modified.
'as' specifies that the argument should be converted to the parameter's type, which may create a temporary value.)"}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ArrayPassedInFunctionArgumentMismatch),
         {"Array passed in function call '{0}' has an argument mismatch. "
          "Expected '{1}', but found '{2}'.",
          "Check the type and dimensions of the array passed to '{0}'. The "
          "function expects a parameter of type '{1}', but an incompatible "
          "type "
          "'{2}' was provided.",
          "Function parameters must match the expected type exactly, "
          "including "
          "array dimensions, element type, and size."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeButArrayDimensionMismatch),
         {"Array passed in function call '{0}' has the correct type '{1}', "
          "but "
          "the array dimensions do not match. Expected dimensions: '{2}', "
          "but "
          "found: '{3}'.",
          "Please adjust the array dimensions to match the expected ones.",
          "Ensure that the number of dimensions and their order match what "
          "the "
          "function '{0}' expects."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ArrayPassedInFunctionArgumentTypeMatchesWithExpectedTypeAndHavingSameDimensionButSizeMismatch),
         {"Array passed in function call '{0}' has the correct type '{1}' "
          "and "
          "matching number of dimensions, but a size mismatch was found in "
          "dimension {2}.",
          "Ensure that the size of the array passed to function '{0}' "
          "matches "
          "the expected size in all dimensions. While the number of "
          "dimensions "
          "is correct, dimension {2} has a size of '{3}' but the function "
          "expects '{4}'.",
          "Array dimensions must not only match in count but also in size "
          "for "
          "each corresponding dimension when passed to this function."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              VariablePassedAsAnArgumentToFunctionIsNotAnArray),
         {"The function '{0}' expects an array parameter of type '{1}', but "
          "a "
          "non-array variable of type '{2}' was provided.",
          "Please provide an array of type '{1}' when calling the function "
          "'{0}'",
          "Ensure that the variable you are passing is an array and matches "
          "the "
          "expected type '{1}'. Using a non-array variable will result in "
          "this "
          "error."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::FunctionArgumentCountMismatch),
         {"The function '{0}' expects at least {1} arguments, but only {2} "
          "were "
          "provided.",
          "Please provide at least {1} arguments when calling the function "
          "'{0}'.",
          "Ensure that the number of arguments passed to the function '{0}' "
          "meets the minimum requirement. It expects at least {1} arguments, "
          "but "
          "{2} were provided."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedTypeExpression),
         {"Unexpected type expression '<{0}>'. Expected one of: '<{1}>', "
          "'<{2}>', '<{3}>', '<{4}>', '<{5}>', '<{6}>', '<{7}>', or '<{8}>'.",
          "Please use a valid type keyword. The function expects one of the "
          "supported types such as '<{1}>' or '<{2}>' etc.",
          "Ensure that the type expression is valid and supported in this "
          "context. Using an unrecognized type like '<{0}>' will result in "
          "this error."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken),
         {"Unexpected token '<{0}>'. Expected '<{1}>'.",
          "Please use a valid token. The expected token is '<{1}>'.",
          "Ensure that the token used is correct and supported in this "
          "context. An unexpected token like '<{0}>' can cause syntax or "
          "parsing errors."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedCharacter),
         {"Unexpected character '<{0}>'. Please use a valid character.",
          "Please use a valid character.",
          "Ensure that the character used is correct and supported in this "
          "context."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleNotFound),
         {"Module '<{0}>' was not found.",
          "Please ensure that the module '<{0}>' exists in the current "
          "directory or is included in the module path.",
          "Verify that the module file '<{0}>' is present in the correct "
          "location and that the path is correctly specified."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::CircularReference),
         {"Found Circular Reference '<{0}>'. Please remove the circular "
          "reference.",
          "Please remove the circular reference to avoid infinite loops.",
          "Circular references can cause compilation errors and should be "
          "resolved by removing the reference to the module that causes the "
          "circular dependency."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidAssignment),
         {"The assignment operation is not allowed for the type.",
          "Please use a valid assignment operation for the type.",
          "Ensure that the assignment operation is valid for the type."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              InvalidAssignmentToUndeclaredVariable),
         {"The variable '{0}' is not declared. Please declare the variable "
          "before assigning a value to it.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              InvalidAssignmentToConstantVariable),
         {"The variable '{0}' is a constant and cannot be assigned a new "
          "value.",
          "Ensure that the variable '{0}' is not declared as a constant if you "
          "intend to assign a value to it.",
          "Constant variables are immutable. To assign a value, use a regular "
          "(non-constant) variable declaration instead."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidBracketedExpression),
         {"Invalid Bracketed Expression, Expected Fill Expression or Container "
          "Expression.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::SuperCallOutsideConstructor),
         {"Cannot call 'super' outside of a constructor.",
          "Ensure that the 'super' function is only called within a class "
          "'init'"
          "constructor function.",
          "'super' must be invoked within the constructor of a derived class "
          "before accessing 'this' or returning from the constructor."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidInitFunctionCall),
         {"Cannot call 'init' function directly inside or outside of a class.",
          "The 'init' function is meant to be invoked by the system during "
          "object construction and should not be called explicitly.",
          "Avoid calling the 'init' function manually. Use a constructor to "
          "create and initialize objects."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::IncorrectArgumentCount),
         {"Function '{0}' requires {1} argument(s), but {2} were provided.",
          "Ensure that the function '{0}' is called with exactly {1} "
          "argument(s).",
          "Check the function definition to confirm the required number of "
          "arguments and match it in the function call."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassMissingSuperclass),
         {"Could not find a superclass for class '{0}'.",
          "Please add a valid superclass to the declaration of class '{0}'.",
          "Every class must inherit from a valid superclass if required by the "
          "context. Ensure that class '{0}' extends an appropriate "
          "base class."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassMissingInitializer),
         {"Class '{0}' does not have an initializer.",
          "Please add a default or parameterized init constructor function to "
          "the body of "
          "class '{0}'.",
          "Initializers define how instances of a class are created. Ensure "
          "that class '{0}' includes at least one initializer (init "
          "constructor function) to "
          "enable proper object construction."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::FunctionNotFound),
         {"Function '{0}' does not exist.",
          "Ensure that the function '{0}' is defined before it is called.",
          "Check for typos in the function name or verify that the function "
          "'{0}' is declared in the current scope or imported correctly."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::VariableNotFound),
         {"Variable '{0}' does not exist.",
          "Ensure that the variable '{0}' is declared before it is used.",
          "Check for typos in the variable name or verify that it is defined "
          "in the current scope."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::IndexingNonArrayVariable),
         {"Variable '{0}' is not an array. Cannot perform indexing operation.",
          "Ensure that variable '{0}' is an array before using index access.",
          "Indexing operations like 'variable[0]' can only be used on array "
          "types. "
          "Using them on non-array variables will result in an error."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::InValidTypeExpression),
         {"Invalid Type Expression kind '{0}'", "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::TypeOrClassNotFound),
         {"Type or class '{0}' was not found.",
          "Ensure that the type or class '{0}' is defined or imported before "
          "use.",
          "Check for spelling errors or missing imports. The type or class "
          "'{0}' must be declared in the current scope."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::FunctionAlreadyDeclared),
         {"Function '{0}' is already declared.",
          "A function with the name '{0}' has already been defined. Please use "
          "a different name or check for duplicate declarations.",
          "Ensure that function names are unique within the same scope to "
          "avoid redeclaration errors."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              MemberFunctionOfClassAlreadyDeclared),
         {"The member function '{0}' is already declared in class.",
          "Avoid redeclaring the same member function within the class.",
          "Each member function must have a unique signature in its class. "
          "Check if the function '{0}' was previously declared."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              FunctionNameConflictsWithBuiltin),
         {"A built-in function named '{0}' already exists.",
          "Please use a different name to avoid conflict with the built-in "
          "function '{0}'.",
          "Defining a function with the same name as a built-in can lead to "
          "unexpected behavior or override issues. Choose a unique name for "
          "your custom function."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              MissingDefaultValueForOptionalParameter),
         {"Missing default value for optional parameter: '{0}' in function "
          "'{1}'.",
          "Please provide a default value for the optional parameter '{0}' in "
          "function '{1}'.",
          "All optional parameters must have default values. Ensure that "
          "parameter '{0}' is properly initialized in the function "
          "declaration."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::InvalidBreakStatementUsage),
         {"'break' statement used outside of a loop or switch.",
          "Use the 'break' statement only within loops (for, while) or switch "
          "blocks.",
          "Placing a 'break' statement outside of valid control structures "
          "like loops or switch statements will result in a syntax error."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::FileNotFound),
         {"File '<{0}>' was not found.",
          "Ensure that the file '<{0}>' exists at the specified path.",
          "Check the relative path and verify that the file is present and "
          "accessible in the expected location."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              IdentifierNotFoundInFileOrModule),
         {"Identifier '<{0}>' not found in '<{1}>'.",
          "Ensure that the identifier '<{0}>' is defined and accessible within "
          "the file/module '<{1}>'.",
          "Check if the identifier is correctly declared and imported. Also, "
          "verify the file/module path '<{1}>' is correct and accessible."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleAlreadyDeclared),
         {"Module '{0}' is already declared.",
          "Avoid declaring the same module '{0}' more than once.",
          "Check for duplicate 'bring' statements referring to "
          "module '{0}' and remove any redundant declarations."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::VariableAlreadyDeclared),
         {"Variable '{0}' is already declared.",
          "Please use a different name or remove the previous declaration of "
          "variable '{0}'.",
          "Multiple declarations of the same variable in the same scope are "
          "not allowed. Consider renaming or reusing the existing variable."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::TypeAlreadyDeclared),
         {"Type <{0}>' is already declared.",
          "A type with the name '<{0}>' has already been defined. Please use a "
          "different name.",
          "Ensure that there are no duplicate type declarations with the same "
          "name in the current scope or imported files/modules."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassAlreadyDeclared),
         {"Class '{0}' is already declared.",
          "Rename the class or remove the duplicate declaration of '{0}'.",
          "Each class must have a unique name within the same scope. Multiple "
          "declarations of class '{0}' are not allowed."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ImportModuleWithErrorsWarning),
         {"Problem encountered while importing module '{0}'. The "
          "module contains unresolved errors.",
          "Please fix the errors in module '{0}' before importing it.",
          "Unresolved errors in the imported module may cause runtime or "
          "compilation issues. Ensure that all dependencies and syntax within "
          "module '{0}' are valid."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              UnSupportedUnaryOperatorForClassType),
         {"Unsupported unary operator '{0}' for class type. Please use a "
          "valid unary operator for class type.",
          "", ""}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::ParentClassNotFound),
         {"Parent class '{0}' not found for class '{1}'.",
          "Ensure that the class '{0}' is defined and accessible before "
          "extending it.",
          "This error may occur if the parent class '{0}' is missing, "
          "misspelled, or not yet declared. "
          "Make sure the definition of '{0}' exists and is in scope when "
          "defining class '{1}'."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ContinueStatementOutsideOfLoop),
         {"'continue' statement not within a loop.",
          "Move the 'continue' statement inside a valid loop (e.g., for or"
          "while loop).",
          "'continue' is only valid inside loops and causes the next iteration "
          "to begin. "
          "Using it outside of a loop results in a syntax error."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              DuplicateAttributeKeyInCustomType),
         {"Duplicate attribute key '{0}' found in custom type '{1}'.",
          "Remove or rename one of the duplicate keys ('{0}') in your custom "
          "type '{1}'.",
          "Having multiple attributes with the same key in a custom type can "
          "lead to ambiguity and unexpected behavior. Make sure each attribute "
          "key is unique."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              DuplicateCustomTypeDeclaration),
         {"Custom type '{0}' is declared multiple times.",
          "Remove the duplicate declaration of custom type '{0}'.",
          "Declaring the same custom type more than once can lead to confusion "
          "or conflicts. Ensure that '{0}' is only defined once"}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              UnsupportedExpressionOrStatementInModule),
         {"Unsupported expression or statement used in module '{0}'.",
          "Please use valid expressions and statements in module '{0}'.",
          "Ensure that the expression or statement is valid and supported in "
          "the module '{0}'."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::DuplicateModuleDeclaration),
         {"Module '{0}' is declared more than once.",
          "Ensure that module '{0}' is only declared once in your code.",
          "Multiple declarations of the same module can lead to conflicts or "
          "unexpected behavior. "
          "Consolidate or remove redundant declarations of module '{0}'."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              ReturnStatementOutsideOfFunction),
         {"'return' statement cannot appear outside of a function body.",
          "Ensure that the 'return' statement is placed inside a function.",
          "'return' is only valid within the context of a function. If used "
          "outside, it will result in a compilation error."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              NoDefaultCaseInSwitchStatement),
         {"Switch statement does not have a default case.",
          "Add a default case to the switch statement to handle unexpected or "
          "unhandled values.",
          "Including a default case ensures that all possible values are "
          "handled, improving code robustness and preventing potential runtime "
          "issues."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              MoreThanOneDefaultCaseInSwitchStatement),
         {"Multiple 'default' cases found in the switch statement. "
          "Only one 'default' case is allowed.",
          "Remove all but one 'default' case from the switch statement.",
          "Having more than one 'default' case leads to ambiguity. A switch "
          "statement must have at most one 'default' case to ensure clear and "
          "predictable control flow."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              NoCaseStatementInSwitchStatement),
         {"The 'switch' statement does not contain any 'case' labels.",
          "Add at least one 'case' label inside the 'switch' statement to "
          "handle specific conditions.",
          "A 'switch' statement without 'case' labels is usually unintended. "
          "Consider whether an 'if' statement might be more appropriate or if "
          "cases were mistakenly omitted."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnTerminatedSingleQuote),
         {"Unterminated single quote detected.",
          "Ensure that the single-quoted character or string is properly "
          "closed with a matching single quote.",
          "A missing closing single quote can lead to parsing errors. Example: "
          "replace 'a with 'a'."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::BadCharacterEscapeSequence),
         {"Invalid escape sequence '\\{0}' encountered.",
          "Use a valid escape character such as \\n, \\t, \\r, \\', \\\\, etc.",
          "Escape sequences must follow valid syntax. Check for typos or "
          "unsupported escape characters like '\\{0}'."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::NumberTooLargeForInt),
         {"The integer literal '{0}' is too large to be represented as a "
          "64-bit signed integer.",
          "Use a smaller integer value that fits within the 64-bit signed "
          "integer range (−9,223,372,036,854,775,808 to "
          "9,223,372,036,854,775,807).",
          "Literals that exceed the range of a 64-bit signed integer may lead "
          "to overflow or unexpected behavior at runtime."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnTerminatedStringLiteral),
         {"Unterminated string literal detected.",
          "Ensure that all string literals are properly closed with a matching "
          "quotation mark.",
          "Unterminated strings can lead to syntax errors and may cause the "
          "compiler to misinterpret subsequent code. Check for missing or "
          "unmatched quotes in your string."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              BadCharacterEscapeSequenceInStringLiteral),
         {"Invalid escape sequence '\\{0}' encountered.",
          "Use a valid escape character such as \\n, \\t, \\\", \\r, \\\\, "
          "etc.",
          "Escape sequences must follow valid syntax. Check for typos or "
          "unsupported escape characters like '\\{0}' in the string literal."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::BadCharacterInput),
         {"Invalid character '{0}' encountered.",
          "Remove or replace the invalid character '{0}' to continue.",
          "Certain characters may not be allowed in identifiers, paths, or "
          "source code. "
          "Make sure the input does not contain any unsupported or special "
          "characters."}},
        {(FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              UnTerminatedTemplateStringLiteral),
         {"Unterminated template string literal detected. The string starting "
          "with a backtick (`) is not properly closed.",
          "Ensure that the template string literal is properly terminated with "
          "a matching backtick (`).",
          "Unterminated template literals can lead to syntax errors or "
          "unexpected behavior. Verify that multiline strings are correctly "
          "enclosed."}},

};