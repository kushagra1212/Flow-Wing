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
#include "src/SemanticAnalyzer/BoundStatements/BoundStatement/BoundStatement.h"
#include <memory>

class BoundReturnStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::vector<std::unique_ptr<BoundExpression>> _returnExpressionList;

public:
  BoundReturnStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Getters
  */
  inline auto getReturnExpressionListRef() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _returnExpressionList;
  }

  /*
    Setters
  */
  inline void addReturnExpression(std::unique_ptr<BoundExpression> expression) {
    _returnExpressionList.push_back(std::move(expression));
  }
};
