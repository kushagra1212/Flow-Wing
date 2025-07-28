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
#include <memory>

class BoundIndexExpression : public BoundExpression {
private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _boundIdentifierExpression;
  std::vector<std::unique_ptr<BoundExpression>> _boundIndexExpressions;
  std::unique_ptr<BoundExpression> _variableExpression;
  bool _isObject = false;
  bool _isSelf = false;

public:
  BoundIndexExpression(const DiagnosticUtils::SourceLocation &location,
                       std::unique_ptr<BoundLiteralExpression<std::any>>
                           boundIdentifierExpression);

  // Getters
  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundLiteralExpression<std::any>> &
  getBoundIdentifierExpression();

  inline const std::vector<std::unique_ptr<BoundExpression>> &
  getBoundIndexExpressions() const {
    return this->_boundIndexExpressions;
  }

  inline auto getVariableExpression() const
      -> const std::unique_ptr<BoundExpression> & {
    return _variableExpression;
  }

  inline auto isObject() const -> bool { return _isObject; }
  inline auto isSelf() const -> bool { return _isSelf; }

  // Setters

  inline void addBoundIndexExpression(
      std::unique_ptr<BoundExpression> boundIndexExpression) {
    this->_boundIndexExpressions.push_back(std::move(boundIndexExpression));
  }

  inline auto
  addVariableExpression(std::unique_ptr<BoundExpression> variableExpression)
      -> void {
    _isObject = true;
    _variableExpression = std::move(variableExpression);
  }

  inline void setIsSelf(bool isSelf) { _isSelf = isSelf; }
};