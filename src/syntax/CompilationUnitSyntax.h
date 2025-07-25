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


#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "MemberSyntax.h"
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
#include "statements/StatementSyntax.h"
class CompilationUnitSyntax {
 private:
  std::vector<std::unique_ptr<MemberSyntax>> _members;
  std::unique_ptr<SyntaxToken<std::any>> _endOfFileToken = nullptr;
  std::vector<SyntaxNode *> _children;

 public:
  const SyntaxKindUtils::SyntaxKind getKind();

  std::vector<std::unique_ptr<MemberSyntax>> &getMembers();

  void addMember(std::unique_ptr<MemberSyntax> member);
  void setEndOfFileToken(std::unique_ptr<SyntaxToken<std::any>> endOfFileToken);

  const std::vector<SyntaxNode *> &getChildren();

  const std::unique_ptr<SyntaxToken<std::any>> &getEndOfFileTokenRef();
};
#endif