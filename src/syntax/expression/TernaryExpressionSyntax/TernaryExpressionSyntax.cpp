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

#include "TernaryExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

const SyntaxKindUtils::SyntaxKind TernaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::TernaryExpression;
}

const std::vector<SyntaxNode *> &TernaryExpressionSyntax::getChildren() {
  if (_children.empty()) {
    if (_conditionExpression)
      _children.emplace_back(_conditionExpression.get());

    if (_questionToken)
      _children.emplace_back(_questionToken.get());

    if (_trueExpression)
      _children.emplace_back(_trueExpression.get());

    if (_colonToken)
      _children.emplace_back(_colonToken.get());

    if (_falseExpression)
      _children.emplace_back(_falseExpression.get());
  }
  return _children;
}

const DiagnosticUtils::SourceLocation
TernaryExpressionSyntax::getSourceLocation() const {
  if (_conditionExpression)
    return _conditionExpression->getSourceLocation();

  if (_questionToken)
    return _questionToken->getSourceLocation();

  if (_trueExpression)
    return _trueExpression->getSourceLocation();

  if (_colonToken)
    return _colonToken->getSourceLocation();

  if (_falseExpression)
    return _falseExpression->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}
