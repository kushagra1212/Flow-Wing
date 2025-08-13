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

#include "VariableExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression,
    const bool isConstant,
    std::unique_ptr<TypeExpressionSyntax> variableTypeExpr)
    : _identifierExpression(std::move(identifierExpression)),
      _variableTypeExpr(std::move(variableTypeExpr)), _isConstant(isConstant) {}

SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax;
}

const std::vector<SyntaxNode *> &VariableExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_identifierExpression.get());
    if (_variableTypeExpr)
      _children.push_back(_variableTypeExpr.get());

    if (_moduleNameorCallExpression)
      _children.push_back(_moduleNameorCallExpression.get());

    if (_newKeyword) {
      _children.push_back(_newKeyword.get());
    }

    if (_selfKeyword)
      _children.push_back(_selfKeyword.get());

    if (_dotExpressionList.size()) {
      for (const auto &item : _dotExpressionList) {
        _children.push_back(item.get());
      }
    }
  }
  return _children;
}

const DiagnosticUtils::SourceLocation
VariableExpressionSyntax::getSourceLocation() const {
  if (_identifierExpression)
    return _identifierExpression->getSourceLocation();
  if (_variableTypeExpr)
    return _variableTypeExpr->getSourceLocation();

  if (_moduleNameorCallExpression)
    return _moduleNameorCallExpression->getSourceLocation();

  if (_newKeyword) {
    return _newKeyword->getSourceLocation();
  }

  if (_selfKeyword)
    return _selfKeyword->getSourceLocation();

  if (_dotExpressionList.size()) {
    return _dotExpressionList[0]->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}
