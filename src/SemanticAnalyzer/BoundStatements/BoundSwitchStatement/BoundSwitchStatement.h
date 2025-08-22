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

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundSourceLocation/BoundSourceLocation.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundCaseStatement/BoundCaseStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <memory>
#include <vector>

class BoundSwitchStatement : public BoundStatement, public BoundSourceLocation {
  std::unique_ptr<BoundExpression> _switchExpression;
  std::vector<std::unique_ptr<BoundCaseStatement>> _boundCaseStatements;
  std::unique_ptr<BoundCaseStatement> _defaultCaseStatement;
  uint64_t _defaultCasesCount = 0;

public:
  BoundSwitchStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline auto
  setSwitchExpression(std::unique_ptr<BoundExpression> switchExpression)
      -> void {
    this->_switchExpression = std::move(switchExpression);
  }

  inline auto
  addCaseStatement(std::unique_ptr<BoundCaseStatement> boundCaseStatement)
      -> void {

    if (boundCaseStatement->getIsDefaultCase()) {
      this->_defaultCasesCount++;
      _defaultCaseStatement = std::move(boundCaseStatement);
      return;
    }

    this->_boundCaseStatements.emplace_back(std::move(boundCaseStatement));
  }

  /*
    Getters
  */

  inline auto getSwitchExpressionRef() const
      -> const std::unique_ptr<BoundExpression> & {
    return this->_switchExpression;
  }

  inline auto getCaseStatementsRef() const
      -> const std::vector<std::unique_ptr<BoundCaseStatement>> & {
    return this->_boundCaseStatements;
  }

  inline auto getHasNoDefaultCase() const -> bool {
    return this->_defaultCasesCount == 0;
  }

  inline auto getHasMoreThanOneDefaultCase() const -> bool {
    return this->_defaultCasesCount > 1;
  }

  inline auto getDefaultCaseStatementRef() const
      -> const std::unique_ptr<BoundCaseStatement> & {
    return this->_defaultCaseStatement;
  }

  inline auto getHasAtLeastOneCaseStatement() const -> bool {
    return this->_boundCaseStatements.size() > 0;
  }
};
