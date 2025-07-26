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

#include "src/SemanticAnalyzer/BoundExpressions/BoundLiteralExpression/BoundLiteralExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundTypeExpression.h"

class BoundObjectTypeExpression : public BoundTypeExpression {
private:
  std::unique_ptr<BoundLiteralExpression<std::any>> _objectTypeIdentifier;
  std::string _typeName;

public:
  BoundObjectTypeExpression(const DiagnosticUtils::SourceLocation &location,
                            const SyntaxKindUtils::SyntaxKind &type);

  virtual std::vector<BoundNode *> getChildren() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;

  inline auto setObjectTypeIdentifier(
      std::unique_ptr<BoundLiteralExpression<std::any>> objectTypeIdentifier)
      -> void {
    this->_objectTypeIdentifier = std::move(objectTypeIdentifier);
  }

  inline auto setTypeName(std::string typeName) -> void {
    this->_objectTypeIdentifier->setValue(typeName);
  }

  inline auto getTypeName() -> const std::string {

    return std::any_cast<std::string>(this->_objectTypeIdentifier->getValue());
  }

  inline auto getObjectTypeIdentifier()
      -> const std::unique_ptr<BoundLiteralExpression<std::any>> & {
    return this->_objectTypeIdentifier;
  }
};
