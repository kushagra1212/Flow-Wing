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

#include "CaseStatementSyntax.h"
#include "src/diagnostics/DiagnosticUtils/SourceLocation.h"
#include "src/syntax/SyntaxKindUtils.h"

const std::vector<SyntaxNode *> &CaseStatementSyntax::getChildren() {
  if (_children.empty()) {
    if (_caseToken)
      _children.emplace_back(_caseToken.get());

    if (_defaultToken)
      _children.emplace_back(_defaultToken.get());

    if (_caseExpression)
      _children.emplace_back(_caseExpression.get());

    if (_colonToken)
      _children.emplace_back(_colonToken.get());

    if (_blockStatement)
      _children.emplace_back(_blockStatement.get());
  }

  return this->_children;
}

SyntaxKindUtils::SyntaxKind CaseStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::CaseStatementSyntax;
}

const DiagnosticUtils::SourceLocation
CaseStatementSyntax::getSourceLocation() const {

  if (_caseToken)
    return _caseToken->getSourceLocation();

  if (_defaultToken)
    return _defaultToken->getSourceLocation();

  if (_caseExpression)
    return _caseExpression->getSourceLocation();

  if (_colonToken)
    return _colonToken->getSourceLocation();

  if (_blockStatement)
    return _blockStatement->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}
