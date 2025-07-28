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

#include "ForStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/BlockStatementParser/BlockStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ExpressionStatementParser/ExpressionStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/VariableDeclarationParser/VariableDeclarationParser.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/statements/ForStatementSyntax/ForStatementSyntax.h"
#include <memory>

std::unique_ptr<StatementSyntax>
ForStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> keyword =
      ctx->match(SyntaxKindUtils::SyntaxKind::ForKeyword);
  ctx->getCodeFormatterRef()->appendWithSpace();
  bool hadOpenParenthesis = false;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::OpenParenthesisToken);
    hadOpenParenthesis = true;
  }

  std::unique_ptr<StatementSyntax> statementSyntax = nullptr;

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::VarKeyword) {
    std::unique_ptr<VariableDeclarationParser> varDecParser =
        std::make_unique<VariableDeclarationParser>();
    // varDecParser->setIsForStatement(true);
    statementSyntax = varDecParser->parseStatement(ctx);
  } else {
    statementSyntax =
        std::make_unique<ExpressionStatementParser>()->parseStatement(ctx);
  }
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<SyntaxToken<std::any>> toKeyword =
      ctx->match(SyntaxKindUtils::SyntaxKind::ToKeyword);
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<ExpressionSyntax> upperBound =
      PrecedenceAwareExpressionParser::parse(ctx);
  std::unique_ptr<ExpressionSyntax> step = nullptr;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
    ctx->getCodeFormatterRef()->appendWithSpace();
    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
    step = PrecedenceAwareExpressionParser::parse(ctx);
  }

  if (hadOpenParenthesis) {
    ctx->match(SyntaxKindUtils::SyntaxKind::CloseParenthesisToken);
  }
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::unique_ptr<BlockStatementSyntax> statement(
      static_cast<BlockStatementSyntax *>(
          std::make_unique<BlockStatementParser>()
              ->parseStatement(ctx)
              .release()));

  return std::make_unique<ForStatementSyntax>(
      std::move(statementSyntax), std::move(upperBound), std::move(statement),
      std::move(step));
}
