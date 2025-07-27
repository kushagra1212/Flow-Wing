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

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include <memory>

class FunctionTypeExpressionSyntax : public TypeExpressionSyntax {
private:
  std::vector<std::unique_ptr<TypeExpressionSyntax>> _parameterTypes;
  std::vector<std::unique_ptr<TypeExpressionSyntax>> _returnTypes;
  std::vector<std::pair<uint64_t, std::unique_ptr<SyntaxToken<std::any>>>>
      _asParametersKeywords;
  std::unique_ptr<SyntaxToken<std::any>> _asKeyword;

  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _separators;
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;
  std::unique_ptr<SyntaxToken<std::any>> _openBracketToken;
  std::unique_ptr<SyntaxToken<std::any>> _closeBracketToken;

public:
  FunctionTypeExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> type);
  const virtual SyntaxKindUtils::SyntaxKind getKind() const override;
  const virtual std::vector<SyntaxNode *> &getChildren() override;
  const virtual DiagnosticUtils::SourceLocation
  getSourceLocation() const override;

  inline auto
  addParameterType(std::unique_ptr<TypeExpressionSyntax> parameterType)
      -> void {
    _parameterTypes.push_back(std::move(parameterType));
  }

  inline auto addReturnType(std::unique_ptr<TypeExpressionSyntax> returnType)
      -> void {
    _returnTypes.push_back(std::move(returnType));
  }

  inline auto addAsParameterKeyword(
      uint64_t index, std::unique_ptr<SyntaxToken<std::any>> asParameterKeyword)
      -> void {
    _asParametersKeywords.push_back({index, std::move(asParameterKeyword)});
  }

  inline auto setAsKeyword(std::unique_ptr<SyntaxToken<std::any>> asKeyword)
      -> void {
    _asKeyword = std::move(asKeyword);
  }

  inline auto setOpenParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken) -> void {
    _openParenthesisToken = std::move(openParenthesisToken);
  }

  inline auto
  setOpenBracketToken(std::unique_ptr<SyntaxToken<std::any>> openBracketToken)
      -> void {
    _openBracketToken = std::move(openBracketToken);
  }

  inline auto
  setCloseBracketToken(std::unique_ptr<SyntaxToken<std::any>> closeBracketToken)
      -> void {
    _closeBracketToken = std::move(closeBracketToken);
  }

  inline auto setCloseParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken) -> void {
    _closeParenthesisToken = std::move(closeParenthesisToken);
  }

  inline auto addSeparator(std::unique_ptr<SyntaxToken<std::any>> separator) {
    _separators.push_back(std::move(separator));
  }

  inline auto getReturnTypesRef() const
      -> const std::vector<std::unique_ptr<TypeExpressionSyntax>> & {
    return _returnTypes;
  }

  inline auto getParameterTypesRef() const
      -> const std::vector<std::unique_ptr<TypeExpressionSyntax>> & {
    return _parameterTypes;
  }

  inline auto getAsKeywordRef() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _asKeyword;
  }

  inline auto getAsParametersKeywordsRef() const -> const std::vector<
      std::pair<uint64_t, std::unique_ptr<SyntaxToken<std::any>>>> & {
    return _asParametersKeywords;
  }
};