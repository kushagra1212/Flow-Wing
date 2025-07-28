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

#pragma once

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/CaseStatementSyntax/CaseStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>

class SwitchStatementSyntax : public StatementSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _switchToken;
  std::unique_ptr<ExpressionSyntax> _switchExpression;
  std::unique_ptr<SyntaxToken<std::any>> _openCurlyToken;
  std::vector<std::unique_ptr<CaseStatementSyntax>> _caseStatements;
  std::unique_ptr<SyntaxToken<std::any>> _closeCurlyToken;

public:
  /*
    Overrides
  */

  const std::vector<SyntaxNode *> &getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Setters
  */

  inline auto
  setSwitchToken(std::unique_ptr<SyntaxToken<std::any>> switchToken) {
    _switchToken = std::move(switchToken);
  }

  inline auto
  setSwitchExpression(std::unique_ptr<ExpressionSyntax> switchExpression) {
    _switchExpression = std::move(switchExpression);
  }

  inline auto
  setOpenCurlyToken(std::unique_ptr<SyntaxToken<std::any>> openCurlyToken) {
    _openCurlyToken = std::move(openCurlyToken);
  }

  inline auto
  addCaseStatement(std::unique_ptr<CaseStatementSyntax> caseStatement) {
    _caseStatements.emplace_back(std::move(caseStatement));
  }

  inline auto
  setCloseCurlyToken(std::unique_ptr<SyntaxToken<std::any>> closeCurlyToken) {
    _closeCurlyToken = std::move(closeCurlyToken);
  }

  /*
    Getters
  */

  inline auto getSwitchExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _switchExpression;
  }

  inline auto getCaseStatementsRef() const
      -> const std::vector<std::unique_ptr<CaseStatementSyntax>> & {
    return _caseStatements;
  }
};
