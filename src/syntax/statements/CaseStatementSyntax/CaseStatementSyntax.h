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

#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../BlockStatementSyntax/BlockStatementSyntax.h"
#include "../StatementSyntax.h"
#include <memory>
#include <vector>

class CaseStatementSyntax : public StatementSyntax {
  std::unique_ptr<SyntaxToken<std::any>> _caseToken;
  std::unique_ptr<ExpressionSyntax> _caseExpression;
  std::unique_ptr<SyntaxToken<std::any>> _defaultToken;
  std::unique_ptr<SyntaxToken<std::any>> _colonToken;
  std::unique_ptr<BlockStatementSyntax> _blockStatement;

public:
  /*
    Overrides
  */

  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Setters
  */

  inline auto setCaseToken(std::unique_ptr<SyntaxToken<std::any>> caseToken)
      -> void {
    _caseToken = std::move(caseToken);
  }

  inline auto
  setDefaultToken(std::unique_ptr<SyntaxToken<std::any>> defaultToken) -> void {
    _defaultToken = std::move(defaultToken);
  }

  inline auto
  setCaseExpression(std::unique_ptr<ExpressionSyntax> caseExpression) -> void {
    _caseExpression = std::move(caseExpression);
  }

  inline auto setColonToken(std::unique_ptr<SyntaxToken<std::any>> colonToken)
      -> void {
    _colonToken = std::move(colonToken);
  }

  inline auto
  setBlockStatement(std::unique_ptr<BlockStatementSyntax> blockStatement)
      -> void {
    _blockStatement = std::move(blockStatement);
  }

  /*
    Getters
  */

  inline auto getCaseExpressionRef() const
      -> const std::unique_ptr<ExpressionSyntax> & {
    return _caseExpression;
  }

  inline auto getBlockStatementRef() const
      -> const std::unique_ptr<BlockStatementSyntax> & {
    return _blockStatement;
  }

  inline auto isDefaultCase() const -> const bool {
    return _defaultToken != nullptr;
  }
};
