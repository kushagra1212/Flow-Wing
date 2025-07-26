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

#include "src/SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"

class BoundArrayVariableExpression : public BoundVariableExpression {
 public:
  BoundArrayVariableExpression(
      const DiagnosticUtils::SourceLocation &location,
      std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
      const bool &isConstant, BoundTypeExpression *variableTypeExp);

  virtual const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  const std::vector<std::unique_ptr<BoundExpression>> &getSizeExpressionsRef()
      const;

  void addSizeExpression(std::unique_ptr<BoundExpression> sizeExpression);

 private:
  std::vector<std::unique_ptr<BoundExpression>> _sizeExpressions;
};
