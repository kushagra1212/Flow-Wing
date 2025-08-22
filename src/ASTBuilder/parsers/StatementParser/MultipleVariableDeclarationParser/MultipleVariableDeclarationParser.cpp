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

#include "MultipleVariableDeclarationParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserUtils/VariableParserUtils.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/statements/MultipleVariableDeclarationSyntax/MultipleVariableDeclarationSyntax.h"

std::unique_ptr<StatementSyntax>
MultipleVariableDeclarationParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<MultipleVariableDeclarationSyntax> mulVarDec =
      std::make_unique<MultipleVariableDeclarationSyntax>();

  mulVarDec->addVariableDeclaration(std::move(_initialVarDec));
  while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
    ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<VariableDeclarationSyntax> varDec =
        std::make_unique<VariableDeclarationSyntax>();
    VariableParserUtils::handleVarDecParseIdentifierAndType(ctx, varDec);
    mulVarDec->addVariableDeclaration(std::move(varDec));
  }

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EqualsToken) {
    ctx->getCodeFormatterRef()->appendWithSpace();
    std::unique_ptr<SyntaxToken<std::any>> equalsToken =
        ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
    uint8_t index = 0;

    do {

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken)
        ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::NewKeyword) {
        mulVarDec->getVariableDeclarationListRef()[index]->setNewKeyword(
            ctx->match(SyntaxKindUtils::SyntaxKind::NewKeyword));
        ctx->getCodeFormatterRef()->appendWithSpace();
      }

      std::unique_ptr<ExpressionSyntax> initializer =
          PrecedenceAwareExpressionParser::parse(ctx);
      mulVarDec->getVariableDeclarationListRef()[index++]->setInitializer(
          std::move(initializer));
    } while (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken);
  }

  return mulVarDec;
}
