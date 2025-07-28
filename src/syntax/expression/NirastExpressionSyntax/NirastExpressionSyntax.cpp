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

#include "NirastExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"

NirastExpressionSyntax::NirastExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> nirastExpression)
    : _nirastExpression(std::move(nirastExpression)) {}

SyntaxKindUtils::SyntaxKind NirastExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::NirastExpression;
}
const std::vector<SyntaxNode *> &NirastExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (_nirastExpression)
    _children.emplace_back(_nirastExpression.get());

  return _children;
}
const DiagnosticUtils::SourceLocation
NirastExpressionSyntax::getSourceLocation() const {

  if (_nirastExpression)
    return _nirastExpression->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}