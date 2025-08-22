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


#include "BoundCaseStatement.h"

BoundCaseStatement::BoundCaseStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

/*
  Overrides
*/

BinderKindUtils::BoundNodeKind BoundCaseStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundCaseStatement;
}

std::vector<BoundNode *> BoundCaseStatement::getChildren() {
  if (_children.empty()) {
    if (_caseExpression)
      _children.emplace_back(_caseExpression.get());

    if (_bodyStatement)
      _children.emplace_back(_bodyStatement.get());
  }

  return _children;
}
