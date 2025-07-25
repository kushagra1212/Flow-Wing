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


#ifndef __FLOWWING_ATTRIBUTE_EXPRESSION_SYNTAX_H__
#define __FLOWWING_ATTRIBUTE_EXPRESSION_SYNTAX_H__
#include "../../../common/Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class AttributeExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _key;
  std::unique_ptr<ExpressionSyntax> _value;

public:
  // Overrides
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  inline auto
  setAttribute(std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
               std::unique_ptr<ExpressionSyntax> value) -> void {
    this->_key = std::move(key);
    this->_value = std::move(value);
  }

  // Getters
  inline auto getKey()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_key;
  }

  inline auto getValue() -> const std::unique_ptr<ExpressionSyntax> & {
    return this->_value;
  }
};

#endif // __FLOWWING_ATTRIBUTE_EXPRESSION_SYNTAX_H__
