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

#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/AttributeExpressionSyntax/AttributeExpressionSyntax.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/TypeExpressionSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"
#include <any>
class CustomTypeStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _typeName;
  std::vector<std::unique_ptr<AttributeExpressionSyntax>> _key_type_pairs;
  std::unique_ptr<SyntaxToken<std::any>> _exposeKeyword;

public:
  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
     Setters
  */

  inline auto
  setTypeName(std::unique_ptr<LiteralExpressionSyntax<std::any>> typeName)
      -> void {
    this->_typeName = std::move(typeName);
  }

  inline auto
  addKeyTypePair(std::unique_ptr<LiteralExpressionSyntax<std::any>> key,
                 std::unique_ptr<TypeExpressionSyntax> type) -> void {
    std::unique_ptr<AttributeExpressionSyntax> key_type_pair =
        std::make_unique<AttributeExpressionSyntax>();

    key_type_pair->setAttribute(std::move(key), std::move(type));

    this->_key_type_pairs.push_back(std::move(key_type_pair));
  }

  inline auto
  setExposeKeyword(std::unique_ptr<SyntaxToken<std::any>> exposeKeyword)
      -> void {
    this->_exposeKeyword = std::move(exposeKeyword);
  }

  /*
    Getters
  */

  inline auto getTypeNameRef()
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return this->_typeName;
  }

  inline auto getKeyTypePairsRef()
      -> const std::vector<std::unique_ptr<AttributeExpressionSyntax>> & {
    return this->_key_type_pairs;
  }

  inline auto isExposed() const -> bool {
    return this->_exposeKeyword != nullptr;
  }
};
