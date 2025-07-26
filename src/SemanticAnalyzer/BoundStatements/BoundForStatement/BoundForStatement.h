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

#include "src/SemanticAnalyzer/BinderKindUtils.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundSourceLocation/BoundSourceLocation.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundForStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::unique_ptr<BoundStatement> _initialization;

  std::unique_ptr<BoundStatement> _statement;

  std::unique_ptr<BoundExpression> _upperBound;

  std::unique_ptr<BoundExpression> _boundStepExpression;

public:
  BoundForStatement(const DiagnosticUtils::SourceLocation &location,
                    std::unique_ptr<BoundStatement> initialization,
                    std::unique_ptr<BoundExpression> upperBound,
                    std::unique_ptr<BoundExpression> boundStepExpression,
                    std::unique_ptr<BoundStatement> statement);

  std::unique_ptr<BoundStatement> getInitialization();

  std::unique_ptr<BoundStatement> getStatement();

  std::unique_ptr<BoundExpression> getUpperBound();

  std::unique_ptr<BoundExpression> getStepExpression();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundStatement> &getInitializationPtr();

  std::unique_ptr<BoundStatement> &getStatementPtr();

  std::unique_ptr<BoundExpression> &getUpperBoundPtr();

  std::unique_ptr<BoundExpression> &getStepExpressionPtr();
};
