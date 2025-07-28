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

#include "SwitchStatementSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

const std::vector<SyntaxNode *> &SwitchStatementSyntax::getChildren() {
  if (_children.empty()) {
    if (_switchToken)
      _children.emplace_back(_switchToken.get());

    if (_switchExpression)
      _children.emplace_back(_switchExpression.get());

    if (_openCurlyToken)
      _children.emplace_back(_openCurlyToken.get());

    for (const auto &caseStatement : _caseStatements)
      _children.emplace_back(caseStatement.get());

    if (_closeCurlyToken)
      _children.emplace_back(_closeCurlyToken.get());
  }

  return this->_children;
}

SyntaxKindUtils::SyntaxKind SwitchStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::SwitchStatementSyntax;
}

const DiagnosticUtils::SourceLocation
SwitchStatementSyntax::getSourceLocation() const {
  if (_switchToken)
    return _switchToken->getSourceLocation();

  if (_switchExpression)
    return _switchExpression->getSourceLocation();

  if (_openCurlyToken)
    return _openCurlyToken->getSourceLocation();

  for (const auto &caseStatement : _caseStatements)
    return caseStatement->getSourceLocation();

  if (_closeCurlyToken)
    return _closeCurlyToken->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}
