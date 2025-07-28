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

#include "VariableDeclarationParser.h"

std::unique_ptr<StatementSyntax>
VariableDeclarationParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<VariableDeclarationSyntax> varDec =
      std::make_unique<VariableDeclarationSyntax>();

  VariableParserUtils::handleVarDecParsePrefixKeywords(ctx, varDec, false);

  VariableParserUtils::handleVarDecParseIdentifierAndType(ctx, varDec,
                                                          m_isForStatement);

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {

    auto mulVarDec = std::make_unique<MultipleVariableDeclarationParser>();
    mulVarDec->setInitialVarDec(std::move(varDec));

    return mulVarDec->parseStatement(ctx);
  }

  VariableParserUtils::handleVarDecParseInitializer(ctx, varDec);

  return varDec;
}

void VariableDeclarationParser::setIsForStatement(bool isForStatement) {
  m_isForStatement = isForStatement;
}