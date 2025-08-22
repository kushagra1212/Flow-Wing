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


#include "BoundContainerStatement.h"

BoundContainerStatement::BoundContainerStatement(
    const DiagnosticUtils::SourceLocation &location, const Utils::type &type,
    std::string variableName)
    : BoundSourceLocation(location), _type(type),
      _variableName(std::move(variableName)) {}

/*
  Overrides
*/

BinderKindUtils::BoundNodeKind BoundContainerStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ContainerStatement;
}

std::vector<BoundNode *> BoundContainerStatement::getChildren() {
  if (_children.size() == 0) {

    for (const auto &exp : this->_containerSizeExpressions) {
      _children.push_back(exp.get());
    }
    _children.push_back(_containerExpression.get());
  }

  return _children;
}

/*
  Setters
*/

/*
  Getters
*/
auto BoundContainerStatement::getVariableNameRef() const
    -> const std::string & {
  return this->_variableName;
}

auto BoundContainerStatement::getContainerTypeRef() const
    -> const Utils::type & {
  return this->_type;
}
