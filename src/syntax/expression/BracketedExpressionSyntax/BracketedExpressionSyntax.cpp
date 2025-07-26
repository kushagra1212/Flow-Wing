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

#include "BracketedExpressionSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

/*
    OVERIDES
*/

const SyntaxKindUtils::SyntaxKind BracketedExpressionSyntax::getKind() const {
  return SyntaxKindUtils::BracketedExpression;
}

const std::vector<SyntaxNode *> &BracketedExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_expression.get());
  }

  return _children;
}

const DiagnosticUtils::SourceLocation
BracketedExpressionSyntax::getSourceLocation() const {
  return _expression->getSourceLocation();
}

/*
    SETTERS
*/

auto BracketedExpressionSyntax::setExpression(
    std::unique_ptr<ExpressionSyntax> expression) -> void {
  _expression = std::move(expression);
}

/*
    GETTERS
*/

auto BracketedExpressionSyntax::getExpressionRef() const
    -> const std::unique_ptr<ExpressionSyntax> & {
  return _expression;
}
