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
#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include <any>
class BoundNirastExpression : public BoundExpression {
  std::unique_ptr<BoundLiteralExpression<std::any>> _nirastExpression;

public:
  BoundNirastExpression(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  inline virtual const std::type_info &getType() override {
    return typeid(BoundNirastExpression);
  }

  /*
    Setters
  */

  inline auto setNirastExpression(
      std::unique_ptr<BoundLiteralExpression<std::any>> nirastExpression)
      -> void {
    this->_nirastExpression = std::move(nirastExpression);
  }

  /*
    Getters
  */

  inline auto getNirastExpressionRef() const
      -> const std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return this->_nirastExpression;
  }
};
