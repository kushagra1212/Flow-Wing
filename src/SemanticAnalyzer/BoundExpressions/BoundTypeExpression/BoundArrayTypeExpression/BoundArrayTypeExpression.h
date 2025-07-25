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

#include "../BoundTypeExpression.h"

class BoundArrayTypeExpression : public BoundTypeExpression {
  std::vector<std::unique_ptr<BoundExpression>> _dimensions;
  SyntaxKindUtils::SyntaxKind _elementType;
  std::unique_ptr<BoundTypeExpression> _boundNonTrivialElementType;
  bool _isTrivialType = false;

public:
  BoundArrayTypeExpression(const DiagnosticUtils::SourceLocation &location,
                           const SyntaxKindUtils::SyntaxKind &type);

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  // Setters
  inline void setElementType(const SyntaxKindUtils::SyntaxKind &type) {
    _isTrivialType = true;
    _elementType = type;
  }

  inline void setNonTrivialElementType(
      std::unique_ptr<BoundTypeExpression> boundNonTrivialElementType) {
    _boundNonTrivialElementType = std::move(boundNonTrivialElementType);
  }

  inline void addDimension(std::unique_ptr<BoundExpression> dimension) {
    _dimensions.push_back(std::move(dimension));
  }

  // Getters

  inline auto getDimensions() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _dimensions;
  }

  inline auto getElementType() const -> const SyntaxKindUtils::SyntaxKind & {
    return _elementType;
  }

  inline auto getNonTrivialElementType() const
      -> const std::unique_ptr<BoundTypeExpression> & {
    return _boundNonTrivialElementType;
  }

  inline bool isTrivialType() const { return _isTrivialType; }
};