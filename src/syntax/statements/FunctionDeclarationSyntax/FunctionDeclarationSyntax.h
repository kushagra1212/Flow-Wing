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

#include "src/syntax/MemberSyntax.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/utils/Utils.h"
class FunctionDeclarationSyntax : public MemberSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _exposedKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _functionKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifierToken;
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::vector<std::unique_ptr<VariableDeclarationSyntax>> _parameters;

  std::vector<std::unique_ptr<SyntaxToken<std::any>>> _separators;

  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;
  std::unique_ptr<BlockStatementSyntax> _body;

  std::unique_ptr<SyntaxToken<std::any>> _asKeyword;
  std::vector<std::unique_ptr<ExpressionSyntax>> _returnTypeExpressionList;
  std::unique_ptr<SyntaxToken<std::any>> _declKeyword;

  std::unique_ptr<TypeExpressionSyntax> _functionType;

  bool _isOnlyDeclared = false;
  bool _isMemberFunction = false;

public:
  std::unique_ptr<SyntaxToken<std::any>> getFunctionKeyword();
  std::unique_ptr<SyntaxToken<std::any>> getIdentifierToken();
  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();
  std::unique_ptr<BlockStatementSyntax> getBody();

  void
  setFunctionKeyword(std::unique_ptr<SyntaxToken<std::any>> functionKeyword);
  void
  setIdentifierToken(std::unique_ptr<SyntaxToken<std::any>> identifierToken);
  void setOpenParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken);
  void addParameter(std::unique_ptr<VariableDeclarationSyntax> parameter);

  void addSeparator(std::unique_ptr<SyntaxToken<std::any>> separator);
  void setCloseParenthesisToken(
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken);
  void setBody(std::unique_ptr<BlockStatementSyntax> body);
  void addReturnExpression(std::unique_ptr<ExpressionSyntax> returnExpression);

  inline auto
  setExposedKeyword(std::unique_ptr<SyntaxToken<std::any>> exposedKeyword) {
    _exposedKeyword = std::move(exposedKeyword);
  }

  auto setIsOnlyDeclared(bool is) { _isOnlyDeclared = is; }

  inline auto
  setDeclKeyword(std::unique_ptr<SyntaxToken<std::any>> declKeyword) {
    this->setIsOnlyDeclared(true);
    _declKeyword = std::move(declKeyword);
  }

  inline auto setAsKeyword(std::unique_ptr<SyntaxToken<std::any>> asKeyword) {
    _asKeyword = std::move(asKeyword);
  }

  inline auto setIsMemberFunction(bool is) { _isMemberFunction = is; }

  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getFunctionKeywordPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getIdentifierTokenPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getOpenParenthesisTokenPtr();
  std::vector<std::unique_ptr<VariableDeclarationSyntax>> &getParametersPtr();

  std::vector<std::unique_ptr<SyntaxToken<std::any>>> &getSeparatorsPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseParenthesisTokenPtr();
  std::unique_ptr<BlockStatementSyntax> &getBodyPtr();

  inline auto getReturnTypeExpressionListRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _returnTypeExpressionList;
  }

  inline auto getDeclKeywordRef() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _declKeyword;
  }

  inline auto isOnlyDeclared() const -> bool { return _isOnlyDeclared; }

  inline auto isExposed() const -> bool { return _exposedKeyword != nullptr; }
  inline auto isMemberFunction() const -> bool { return _isMemberFunction; }

  inline auto getAsKeyword() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _asKeyword;
  }
  inline auto
  setFunctionType(std::unique_ptr<TypeExpressionSyntax> functionType) {
    _functionType = std::move(functionType);
  }

  inline auto getFunctionTypeRef() const
      -> const std::unique_ptr<TypeExpressionSyntax> & {
    return _functionType;
  }
};
