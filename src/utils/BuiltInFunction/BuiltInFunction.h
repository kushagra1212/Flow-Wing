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


#pragma once

#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundFunctionDeclaration/BoundFunctionDeclaration.h"

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
