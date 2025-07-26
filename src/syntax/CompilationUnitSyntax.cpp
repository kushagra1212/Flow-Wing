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

#include "CompilationUnitSyntax.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"

const SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

std::vector<std::unique_ptr<MemberSyntax>> &
CompilationUnitSyntax::getMembers() {
  return this->_members;
}

void CompilationUnitSyntax::addMember(std::unique_ptr<MemberSyntax> member) {
  this->_members.push_back(std::move(member));
}

void CompilationUnitSyntax::setEndOfFileToken(
    std::unique_ptr<SyntaxToken<std::any>> endOfFileToken) {
  this->_endOfFileToken = std::move(endOfFileToken);
}

const std::vector<SyntaxNode *> &CompilationUnitSyntax::getChildren() {
  if (this->_children.empty()) {
    // Add Children
    for (const auto &member : this->_members) {
      _children.emplace_back((SyntaxNode *)(member.get()));
    }
    _children.emplace_back(this->_endOfFileToken.get());
  }
  return this->_children;
}

const std::unique_ptr<SyntaxToken<std::any>> &
CompilationUnitSyntax::getEndOfFileTokenRef() {
  return this->_endOfFileToken;
}
