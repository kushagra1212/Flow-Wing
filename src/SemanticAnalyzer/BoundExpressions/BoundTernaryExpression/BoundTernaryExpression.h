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
#include <memory>

class BoundTernaryExpression : public BoundExpression {
public:
  BoundTernaryExpression(const DiagnosticUtils::SourceLocation &location,
                         std::unique_ptr<BoundExpression> conditionExpression,
                         std::unique_ptr<BoundExpression> trueExpression,
                         std::unique_ptr<BoundExpression> falseExpression);

  inline const std::unique_ptr<BoundExpression> &
  getConditionExpressionRef() const {
    return _conditionExpression;
  }
  inline const std::unique_ptr<BoundExpression> &getTrueExpressionRef() const {
    return _trueExpression;
  }
  inline const std::unique_ptr<BoundExpression> &getFalseExpressionRef() const {
    return _falseExpression;
  }

  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

private:
  std::unique_ptr<BoundExpression> _conditionExpression;
  std::unique_ptr<BoundExpression> _trueExpression;
  std::unique_ptr<BoundExpression> _falseExpression;
};