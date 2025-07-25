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


#include "BoundSwitchStatement.h"

BoundSwitchStatement::BoundSwitchStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

/*
  Overrides
*/

BinderKindUtils::BoundNodeKind BoundSwitchStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundSwitchStatement;
}

std::vector<BoundNode *> BoundSwitchStatement::getChildren() {
  if (_children.empty()) {
    if (_switchExpression)
      _children.emplace_back(_switchExpression.get());

    for (auto &item : _boundCaseStatements) {
      _children.emplace_back(item.get());
    }

    if (_defaultCaseStatement)
      _children.emplace_back(_defaultCaseStatement.get());
  }

  return _children;
}
