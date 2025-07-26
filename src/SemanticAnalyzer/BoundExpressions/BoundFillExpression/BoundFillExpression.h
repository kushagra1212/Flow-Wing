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


#ifndef __FLOWWING_BOUND_FILL_EXPRESSION_H__
#define __FLOWWING_BOUND_FILL_EXPRESSION_H__

#include "src/SemanticAnalyzer/BoundExpressions/BoundExpression/BoundExpression.h"

class BoundFillExpression : public BoundExpression {
private:
  std::unique_ptr<BoundExpression> _elementToFill;
  std::unique_ptr<BoundExpression> _sizeToFill;

public:
  BoundFillExpression(const DiagnosticUtils::SourceLocation &location);

  // OVERRIDES
  const std::type_info &getType() override;
  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  // SETTERS
  void setElementToFill(std::unique_ptr<BoundExpression> elementToFill);
  void setSizeToFill(std::unique_ptr<BoundExpression> sizeToFill);

  // GETTERS
  auto getElementToFillRef() const -> const std::unique_ptr<BoundExpression> &;
  auto getSizeToFillRef() const -> const std::unique_ptr<BoundExpression> &;
};

#endif // __FLOWWING_BOUND_FILL_EXPRESSION_H__