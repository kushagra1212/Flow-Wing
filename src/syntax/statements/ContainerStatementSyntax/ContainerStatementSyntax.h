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


#ifndef __CONTAINER_STATEMENT_SYNTAX_H__
#define __CONTAINER_STATEMENT_SYNTAX_H__

#include "../../../utils/Utils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../../expression/ContainerExpressionSyntax/ContainerExpressionSyntax.h"
#include "../../expression/ExpressionSyntax.h"
#include "../../expression/LiteralExpressionSyntax.h"
#include "../StatementSyntax.h"

class ContainerStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _keyword;
  std::unique_ptr<SyntaxToken<std::any>> _identifierToken;
  std::unique_ptr<ExpressionSyntax> _containerExpression;
  std::vector<std::unique_ptr<ExpressionSyntax>> _containerSizeExpressions;

  Utils::type _type;

 public:
  ContainerStatementSyntax() = default;

  // Overrides
  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  auto setContainerExpression(
      std::unique_ptr<ExpressionSyntax> containerExpression) -> void;
  auto setIdentifierToken(
      std::unique_ptr<SyntaxToken<std::any>> identifierToken) -> void;
  auto setType(Utils::type type) -> void;
  auto addContainerSizeExpression(std::unique_ptr<ExpressionSyntax> item)
      -> void;
  auto setKeyword(std::unique_ptr<SyntaxToken<std::any>> keyword) -> void;

  // Getters
  const std::unique_ptr<SyntaxToken<std::any>> &getIdentifierTokenRef() const;
  const std::unique_ptr<ExpressionSyntax> &getContainerExpressionRef() const;

  inline const std::vector<std::unique_ptr<ExpressionSyntax>> &
  getContainerSizeExpressionsRef() const {
    return this->_containerSizeExpressions;
  }

  const Utils::type &getType() const;
};

#endif  // __CONTAINER_STATEMENT_SYNTAX_H__