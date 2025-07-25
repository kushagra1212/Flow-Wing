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


#include "BlockStatementSyntax.h"

BlockStatementSyntax::BlockStatementSyntax() {}

std::unique_ptr<SyntaxToken<std::any>>
BlockStatementSyntax::getOpenBraceToken() {
  return std::move(this->_openBraceToken);
}

std::vector<std::unique_ptr<StatementSyntax>> &
BlockStatementSyntax::getStatements() {
  return this->_statements;
}

std::unique_ptr<SyntaxToken<std::any>>
BlockStatementSyntax::getCloseBraceToken() {
  return std::move(this->_closeBraceToken);
}

void BlockStatementSyntax::addStatement(
    std::unique_ptr<StatementSyntax> statement) {
  this->_statements.push_back(std::move(statement));
}

void BlockStatementSyntax::setOpenBraceToken(
    std::unique_ptr<SyntaxToken<std::any>> openBraceToken) {
  this->_openBraceToken = std::move(openBraceToken);
}

void BlockStatementSyntax::setCloseBraceToken(
    std::unique_ptr<SyntaxToken<std::any>> closeBraceToken) {
  this->_closeBraceToken = std::move(closeBraceToken);
}

const SyntaxKindUtils::SyntaxKind BlockStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BlockStatement;
}

const std::vector<SyntaxNode *> &BlockStatementSyntax::getChildren() {
  if (this->_children.empty()) {
    // Add children
    this->_children.push_back(this->_openBraceToken.get());
    for (const auto &statement : this->getStatements()) {
      this->_children.push_back(statement.get());
    }
    this->_children.push_back(this->_closeBraceToken.get());
  }
  return this->_children;
}

const DiagnosticUtils::SourceLocation BlockStatementSyntax::getSourceLocation()
    const {
  return this->_openBraceToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
BlockStatementSyntax::getOpenBraceTokenPtr() {
  return this->_openBraceToken;
}

std::unique_ptr<SyntaxToken<std::any>> &
BlockStatementSyntax::getCloseBraceTokenPtr() {
  return this->_closeBraceToken;
}