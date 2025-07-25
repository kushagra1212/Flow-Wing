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

#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundBlockStatement/BoundBlockStatement.h"
#include "../BoundStatement/BoundStatement.h"

class BoundCaseStatement : public BoundStatement, public BoundSourceLocation {
  bool _isDefaultCase = false;
  std::unique_ptr<BoundExpression> _caseExpression;
  std::unique_ptr<BoundStatement> _bodyStatement;

public:
  BoundCaseStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Setters
  */
  inline auto setIsDefaultCase(const bool &isDefaultCase) -> void {
    this->_isDefaultCase = isDefaultCase;
  }
  inline auto setCaseExpression(std::unique_ptr<BoundExpression> caseExpression)
      -> void {
    this->_caseExpression = std::move(caseExpression);
  }
  inline auto setBodyStatement(std::unique_ptr<BoundStatement> bodyStatement)
      -> void {
    this->_bodyStatement = std::move(bodyStatement);
  }

  /*
    Getters
  */

  inline auto getIsDefaultCase() const -> const bool & {
    return this->_isDefaultCase;
  }
  inline auto getCaseExpressionRef() const
      -> const std::unique_ptr<BoundExpression> & {
    return this->_caseExpression;
  }
  inline auto getBodyStatementRef() const
      -> const std::unique_ptr<BoundStatement> & {
    return this->_bodyStatement;
  }
};
