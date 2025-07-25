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

#include "../../BinderKindUtils.h"
#include "../../BoundExpressions/BoundExpression/BoundExpression.h"
#include "../../BoundSourceLocation/BoundSourceLocation.h"
#include "../../BoundStatements/BoundOrIfStatement/BoundOrIfStatement.h"
#include "../../BoundStatements/BoundStatement/BoundStatement.h"

class BoundIfStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::unique_ptr<BoundExpression> _condition;
  std::unique_ptr<BoundStatement> _thenStatement;
  std::unique_ptr<BoundStatement> _elseStatement;

  std::vector<std::unique_ptr<BoundOrIfStatement>> _orIfStatements;

public:
  BoundIfStatement(const DiagnosticUtils::SourceLocation &location);

  std::unique_ptr<BoundExpression> getCondition();
  std::unique_ptr<BoundStatement> getThenStatement();
  std::unique_ptr<BoundStatement> getElseStatement();

  void addCondition(std::unique_ptr<BoundExpression> condition);
  void addThenStatement(std::unique_ptr<BoundStatement> thenStatement);
  void addOrIfStatement(std::unique_ptr<BoundOrIfStatement> orIfStatement);
  void addElseStatement(std::unique_ptr<BoundStatement> elseStatement);

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getConditionPtr();
  std::unique_ptr<BoundStatement> &getThenStatementPtr();
  std::unique_ptr<BoundStatement> &getElseStatementPtr();
  std::vector<std::unique_ptr<BoundOrIfStatement>> &getOrIfStatementsPtr();
};