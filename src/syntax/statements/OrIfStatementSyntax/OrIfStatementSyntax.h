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
#include "src/syntax/statements/StatementSyntax.h"
#include <any>

template <typename T> class SyntaxToken;
class ExpressionSyntax;
class BlockStatementSyntax;

class OrIfStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> orKeyword;
  std::unique_ptr<SyntaxToken<std::any>> ifKeyword;
  std::unique_ptr<ExpressionSyntax> condition;
  std::unique_ptr<BlockStatementSyntax> statement;

public:
  OrIfStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> orKeyword,
                      std::unique_ptr<SyntaxToken<std::any>> ifKeyword,
                      std::unique_ptr<ExpressionSyntax> condition,
                      std::unique_ptr<BlockStatementSyntax> statement);

  std::unique_ptr<SyntaxToken<std::any>> getOrKeyword();
  std::unique_ptr<SyntaxToken<std::any>> getIfKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getStatement();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOrKeywordPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getIfKeywordPtr();
  std::unique_ptr<ExpressionSyntax> &getConditionPtr();
  std::unique_ptr<BlockStatementSyntax> &getStatementPtr();
};
