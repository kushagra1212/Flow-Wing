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


#include "ContainerStatementSyntax.h"

/*
  OVERRIDES
*/

const std::vector<SyntaxNode *> &ContainerStatementSyntax::getChildren() {
  if (_children.size() > 0) return _children;

  _children.push_back(this->_identifierToken.get());

  for (const auto &exp : this->_containerSizeExpressions) {
    _children.push_back(exp.get());
  }
  _children.push_back(this->_containerExpression.get());

  return _children;
}

const SyntaxKindUtils::SyntaxKind ContainerStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContainerStatement;
}

const DiagnosticUtils::SourceLocation
ContainerStatementSyntax::getSourceLocation() const {
  return this->_identifierToken->getSourceLocation();
}

/*
  SETTERS
*/

auto ContainerStatementSyntax::setContainerExpression(
    std::unique_ptr<ExpressionSyntax> containerExpression) -> void {
  this->_containerExpression = std::move(containerExpression);
}

auto ContainerStatementSyntax::addContainerSizeExpression(
    std::unique_ptr<ExpressionSyntax> exp) -> void {
  this->_containerSizeExpressions.push_back(std::move(exp));
}

auto ContainerStatementSyntax::setIdentifierToken(
    std::unique_ptr<SyntaxToken<std::any>> identifierToken) -> void {
  this->_identifierToken = std::move(identifierToken);
}

auto ContainerStatementSyntax::setType(Utils::type type) -> void {
  this->_type = type;
}

auto ContainerStatementSyntax::setKeyword(
    std::unique_ptr<SyntaxToken<std::any>> keyword) -> void {
  this->_keyword = std::move(keyword);
}

/*
  GETTERS
*/

const std::unique_ptr<SyntaxToken<std::any>> &
ContainerStatementSyntax::getIdentifierTokenRef() const {
  return this->_identifierToken;
}

const Utils::type &ContainerStatementSyntax::getType() const {
  return this->_type;
}

const std::unique_ptr<ExpressionSyntax> &
ContainerStatementSyntax::getContainerExpressionRef() const {
  return this->_containerExpression;
}
