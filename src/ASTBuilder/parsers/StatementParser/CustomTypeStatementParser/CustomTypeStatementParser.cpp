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

#include "CustomTypeStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/common/constants/FlowWingUtilsConstants.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/utils/CustomTypeIDGenerator/CustomTypeIDGenerator.h"
#include "src/utils/LogConfig.h"

std::unique_ptr<StatementSyntax>
CustomTypeStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<CustomTypeStatementSyntax> customTypeStatement =
      std::make_unique<CustomTypeStatementSyntax>();

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    customTypeStatement->setExposeKeyword(
        ctx->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword));
    ctx->getCodeFormatterRef()->appendWithSpace();
  }
  ctx->match(SyntaxKindUtils::SyntaxKind::TypeKeyword);
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::any val = "";
  std::unique_ptr<SyntaxToken<std::any>> typeToken =
      ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
  ctx->getCodeFormatterRef()->appendWithSpace();

  std::string MODULE_PREFIX = "";

  if (ctx->getCurrentModuleName() != "") {

    MODULE_PREFIX =
        ctx->getCurrentModuleName() + FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX;
  }

  if (typeToken->getValue().type() == typeid(std::string)) {
    const std::string PREFIX =
        MODULE_PREFIX + std::any_cast<std::string>(typeToken->getValue());
    val = PREFIX + FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
          IDGenerator::CustomTypeIDGenerator::instance()->nextString();
    //! CHECK
    typeToken->setValue(val);
    typeToken->setText(std::any_cast<std::string>(val));
  }
  DEBUG_LOG("Declared Type: %s", std::any_cast<std::string>(val).c_str());
  std::unique_ptr<LiteralExpressionSyntax<std::any>> typeNameExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(typeToken),
                                                          val);

  customTypeStatement->setTypeName(std::move(typeNameExp));

  ctx->match(SyntaxKindUtils::SyntaxKind::EqualsToken);
  ctx->getCodeFormatterRef()->appendWithSpace();
  ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken);
  ctx->getCodeFormatterRef()->appendNewLine();
  ctx->getCodeFormatterRef()->appendIndentAmount(TAB_SPACE);
  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken &&
         ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());

    std::unique_ptr<SyntaxToken<std::any>> idenfierToken =
        ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);

    std::any localVal = idenfierToken->getValue();

    std::unique_ptr<LiteralExpressionSyntax<std::any>> idenfierExp =
        std::make_unique<LiteralExpressionSyntax<std::any>>(
            std::move(idenfierToken), localVal);

    ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<TypeExpressionSyntax> typeExpression(
        static_cast<TypeExpressionSyntax *>(
            std::make_unique<TypeExpressionParser>()
                ->parseExpression(ctx)
                .release()));

    customTypeStatement->addKeyTypePair(std::move(idenfierExp),
                                        std::move(typeExpression));

    if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
    }
    ctx->getCodeFormatterRef()->appendNewLine();
  }

  ctx->getCodeFormatterRef()->setIndentAmount(
      ctx->getCodeFormatterRef()->getIndentAmount().substr(
          0, ctx->getCodeFormatterRef()->getIndentAmount().length() -
                 (sizeof(TAB_SPACE) - 1)));

  ctx->getCodeFormatterRef()->append(
      ctx->getCodeFormatterRef()->getIndentAmount());

  ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
  return customTypeStatement;
}
