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
#include <memory>
template <typename T> class SyntaxToken;

class BlockStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _openBraceToken;
  std::vector<std::unique_ptr<StatementSyntax>> _statements;
  std::unique_ptr<SyntaxToken<std::any>> _closeBraceToken;

public:
  BlockStatementSyntax();

  void addStatement(std::unique_ptr<StatementSyntax> statement);
  void setOpenBraceToken(std::unique_ptr<SyntaxToken<std::any>> openBraceToken);
  void
  setCloseBraceToken(std::unique_ptr<SyntaxToken<std::any>> closeBraceToken);

  std::unique_ptr<SyntaxToken<std::any>> getOpenBraceToken();
  std::vector<std::unique_ptr<StatementSyntax>> &getStatements();
  std::unique_ptr<SyntaxToken<std::any>> getCloseBraceToken();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOpenBraceTokenPtr();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseBraceTokenPtr();
};