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

#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <memory>

class ForStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<StatementSyntax> _initialization;
  std::unique_ptr<BlockStatementSyntax> _statement;
  std::unique_ptr<ExpressionSyntax> _upperBound;
  std::unique_ptr<ExpressionSyntax> _stepExpression;

public:
  ForStatementSyntax(std::unique_ptr<StatementSyntax> initialization,
                     std::unique_ptr<ExpressionSyntax> upperBound,
                     std::unique_ptr<BlockStatementSyntax> statement,
                     std::unique_ptr<ExpressionSyntax> stepExpression);

  std::unique_ptr<BlockStatementSyntax> getStatement();
  std::unique_ptr<StatementSyntax> getInitialization();
  std::unique_ptr<ExpressionSyntax> getUpperBound();
  std::unique_ptr<ExpressionSyntax> getStepExpression();

  const std::vector<SyntaxNode *> &getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<BlockStatementSyntax> &getStatementRef();
  std::unique_ptr<StatementSyntax> &getInitializationRef();
  std::unique_ptr<ExpressionSyntax> &getUpperBoundRef();
  std::unique_ptr<ExpressionSyntax> &getStepExpressionRef();
};
