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

#include "BoundBracketedExpression.h"
#include "src/SemanticAnalyzer/BinderKindUtils.h"

BoundBracketedExpression::BoundBracketedExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}
/*
    OVERRIDES
*/

const std::type_info &BoundBracketedExpression::getType() {
  return typeid(BoundBracketedExpression);
}

BinderKindUtils::BoundNodeKind BoundBracketedExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundBracketedExpression;
}

std::vector<BoundNode *> BoundBracketedExpression::getChildren() {

  if (_children.size() > 0)
    return _children;

  _children.push_back(_expression.get());
  return _children;
}

/*
    SETTERS
*/

void BoundBracketedExpression::setExpression(
    std::unique_ptr<BoundExpression> expression) {
  _expression = std::move(expression);
}

/*
    GETTERS
*/

auto BoundBracketedExpression::getExpressionRef() const
    -> const std::unique_ptr<BoundExpression> & {
  return _expression;
}
