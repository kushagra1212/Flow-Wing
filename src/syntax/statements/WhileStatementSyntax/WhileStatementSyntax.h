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
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"

#include <any>
#include <memory>

class ExpressionSyntax;
class BlockStatementSyntax;

template <typename T> class SyntaxToken;

class WhileStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _whileKeyword;
  std::unique_ptr<ExpressionSyntax> _condition;
  std::unique_ptr<BlockStatementSyntax> _body;

public:
  WhileStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> whileKeyword,
                       std::unique_ptr<ExpressionSyntax> condition,
                       std::unique_ptr<BlockStatementSyntax> body);

  std::unique_ptr<SyntaxToken<std::any>> getWhileKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getBody();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getWhileKeywordRef();
  std::unique_ptr<ExpressionSyntax> &getConditionRef();
  std::unique_ptr<BlockStatementSyntax> &getBodyRef();
};