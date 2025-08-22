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

#include "OrIfStatementSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"

OrIfStatementSyntax::OrIfStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> orKeyword,
    std::unique_ptr<SyntaxToken<std::any>> ifKeyword,
    std::unique_ptr<ExpressionSyntax> condition,
    std::unique_ptr<BlockStatementSyntax> statement) {
  this->orKeyword = std::move(orKeyword);
  this->ifKeyword = std::move(ifKeyword);
  this->condition = std::move(condition);
  this->statement = std::move(statement);
}

std::unique_ptr<SyntaxToken<std::any>> OrIfStatementSyntax::getIfKeyword() {
  return std::move(ifKeyword);
}

std::unique_ptr<ExpressionSyntax> OrIfStatementSyntax::getCondition() {
  return std::move(condition);
}

std::unique_ptr<BlockStatementSyntax> OrIfStatementSyntax::getStatement() {
  return std::move(statement);
}

std::unique_ptr<SyntaxToken<std::any>> OrIfStatementSyntax::getOrKeyword() {
  return std::move(orKeyword);
}

SyntaxKindUtils::SyntaxKind OrIfStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::OrIfStatement;
}

const DiagnosticUtils::SourceLocation
OrIfStatementSyntax::getSourceLocation() const {
  return this->ifKeyword->getSourceLocation();
}

const std::vector<SyntaxNode *> &OrIfStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    _children.push_back(this->orKeyword.get());
    _children.push_back(this->ifKeyword.get());
    _children.push_back(this->condition.get());
    _children.push_back(this->statement.get());
  }

  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>> &OrIfStatementSyntax::getIfKeywordPtr() {
  return this->ifKeyword;
}
std::unique_ptr<ExpressionSyntax> &OrIfStatementSyntax::getConditionPtr() {
  return this->condition;
}
std::unique_ptr<BlockStatementSyntax> &OrIfStatementSyntax::getStatementPtr() {
  return this->statement;
}
std::unique_ptr<SyntaxToken<std::any>> &OrIfStatementSyntax::getOrKeywordPtr() {
  return this->orKeyword;
}