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

#include "WhileStatementSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"

WhileStatementSyntax::WhileStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> whileKeyword,
    std::unique_ptr<ExpressionSyntax> condition,
    std::unique_ptr<BlockStatementSyntax> body) {
  this->_whileKeyword = std::move(whileKeyword);
  this->_condition = std::move(condition);
  this->_body = std::move(body);
}

std::unique_ptr<SyntaxToken<std::any>> WhileStatementSyntax::getWhileKeyword() {
  return std::move(_whileKeyword);
}

std::unique_ptr<ExpressionSyntax> WhileStatementSyntax::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BlockStatementSyntax> WhileStatementSyntax::getBody() {
  return std::move(_body);
}

SyntaxKindUtils::SyntaxKind WhileStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::WhileStatement;
}

const std::vector<SyntaxNode *> &WhileStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_whileKeyword.get());
    _children.push_back(_condition.get());
    _children.push_back(_body.get());
  }
  return this->_children;
}

const DiagnosticUtils::SourceLocation
WhileStatementSyntax::getSourceLocation() const {
  return this->_whileKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
WhileStatementSyntax::getWhileKeywordRef() {
  return this->_whileKeyword;
}

std::unique_ptr<ExpressionSyntax> &WhileStatementSyntax::getConditionRef() {
  return this->_condition;
}

std::unique_ptr<BlockStatementSyntax> &WhileStatementSyntax::getBodyRef() {
  return this->_body;
}