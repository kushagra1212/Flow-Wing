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
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"
#include "src/syntax/statements/StatementSyntax.h"

#include <any>
#include <memory>
#include <vector>

template <typename T> class SyntaxToken;
class ExpressionSyntax;
class BlockStatementSyntax;
class ElseClauseSyntax;
class OrIfStatementSyntax;

class IfStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> ifKeyword;
  std::unique_ptr<ExpressionSyntax> condition;
  std::unique_ptr<BlockStatementSyntax> statement;
  std::unique_ptr<ElseClauseSyntax> elseClause;

  std::vector<std::unique_ptr<OrIfStatementSyntax>> orIfStatements;

public:
  IfStatementSyntax();

  std::unique_ptr<SyntaxToken<std::any>> getIfKeyword();
  std::unique_ptr<ExpressionSyntax> getCondition();
  std::unique_ptr<BlockStatementSyntax> getStatement();
  std::unique_ptr<ElseClauseSyntax> getElseClause();

  void addIfKeyword(std::unique_ptr<SyntaxToken<std::any>> ifKeyword);
  void addCondition(std::unique_ptr<ExpressionSyntax> condition);
  void addStatement(std::unique_ptr<BlockStatementSyntax> statement);
  void addOrIfStatement(std::unique_ptr<OrIfStatementSyntax> orIfStatement);
  void addElseClause(std::unique_ptr<ElseClauseSyntax> elseClause);

  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getIfKeywordRef();
  std::unique_ptr<ExpressionSyntax> &getConditionRef();
  std::unique_ptr<BlockStatementSyntax> &getStatementRef();
  std::unique_ptr<ElseClauseSyntax> &getElseClauseRef();
  std::vector<std::unique_ptr<OrIfStatementSyntax>> &getOrIfStatementsRef();
};
