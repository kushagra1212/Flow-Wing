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
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"

class ClassStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _exposeKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _classKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _extendsKeyword;
  std::unique_ptr<SyntaxToken<std::any>> _classNameIdentifier;
  std::unique_ptr<SyntaxToken<std::any>> _parentClassNameIdentifier;
  std::unique_ptr<SyntaxToken<std::any>> _classOpenBraceToken;
  std::unique_ptr<SyntaxToken<std::any>> _classCloseBraceToken;
  std::vector<std::unique_ptr<VariableDeclarationSyntax>> _classDataMembers;
  std::vector<std::unique_ptr<FunctionDeclarationSyntax>> _classMemberFunctions;
  std::vector<std::unique_ptr<CustomTypeStatementSyntax>> _customTypeStatements;

public:
  ClassStatementSyntax();
  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  inline auto
  setClassKeyword(std::unique_ptr<SyntaxToken<std::any>> classKeyword) -> void {
    _classKeyword = std::move(classKeyword);
  }
  inline auto
  setClassNameIdentifier(std::unique_ptr<SyntaxToken<std::any>> classNameIden)
      -> void {
    _classNameIdentifier = std::move(classNameIden);
  }

  inline auto setParentClassNameIdentifier(
      std::unique_ptr<SyntaxToken<std::any>> parentClassNameIden) -> void {
    _parentClassNameIdentifier = std::move(parentClassNameIden);
  }

  inline auto setClassOpenBraceToken(
      std::unique_ptr<SyntaxToken<std::any>> classOpenBraceToken) -> void {
    _classOpenBraceToken = std::move(classOpenBraceToken);
  }

  inline auto setClassCloseBraceToken(
      std::unique_ptr<SyntaxToken<std::any>> classCloseBraceToken) -> void {
    _classCloseBraceToken = std::move(classCloseBraceToken);
  }

  inline auto
  setExposeKeyword(std::unique_ptr<SyntaxToken<std::any>> exposeKeyword)
      -> void {
    _exposeKeyword = std::move(exposeKeyword);
  }

  inline auto
  setExtendsKeyword(std::unique_ptr<SyntaxToken<std::any>> extendsKeyword)
      -> void {
    _extendsKeyword = std::move(extendsKeyword);
  }

  inline auto
  addClassDataMember(std::unique_ptr<VariableDeclarationSyntax> member)
      -> void {
    _classDataMembers.push_back(std::move(member));
  }

  inline auto addCustomTypeStatement(
      std::unique_ptr<CustomTypeStatementSyntax> customTypeStatement) -> void {
    _customTypeStatements.push_back(std::move(customTypeStatement));
  }

  inline auto
  addClassMemberFunction(std::unique_ptr<FunctionDeclarationSyntax> function)
      -> void {
    _classMemberFunctions.push_back(std::move(function));
  }

  inline auto getClassNameIdentifierRef()
      -> std::unique_ptr<SyntaxToken<std::any>> & {
    return _classNameIdentifier;
  }

  inline auto getParentClassNameIdentifierRef()
      -> std::unique_ptr<SyntaxToken<std::any>> & {
    return _parentClassNameIdentifier;
  }

  inline auto getExtendsKeywordRef()
      -> std::unique_ptr<SyntaxToken<std::any>> & {
    return _extendsKeyword;
  }

  inline auto getDataMembersRef()
      -> std::vector<std::unique_ptr<VariableDeclarationSyntax>> & {
    return _classDataMembers;
  }

  inline auto getClassMemberFunctionsRef()
      -> std::vector<std::unique_ptr<FunctionDeclarationSyntax>> & {
    return _classMemberFunctions;
  }

  inline auto getExposeKeywordRef()
      -> std::unique_ptr<SyntaxToken<std::any>> & {
    return _exposeKeyword;
  }

  inline auto getCustomTypeStatementsRef()
      -> std::vector<std::unique_ptr<CustomTypeStatementSyntax>> & {
    return _customTypeStatements;
  }
};
