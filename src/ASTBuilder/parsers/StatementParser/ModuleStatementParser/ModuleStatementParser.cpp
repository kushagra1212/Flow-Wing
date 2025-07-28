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

#include "ModuleStatementParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ExpressionParser/CallExpressionParser/CallExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/LiteralExpressionParserUtils/LiteralExpressionParserUtils.h"
#include "src/ASTBuilder/parsers/ParserUtils/VariableParserUtils.h"
#include "src/ASTBuilder/parsers/StatementParser/ClassStatementParser/ClassStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/CustomTypeStatementParser/CustomTypeStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/FunctionDeclarationParser/FunctionDeclarationParser.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include <memory>

std::unique_ptr<StatementSyntax>
ModuleStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<ModuleStatementSyntax> moduleStatement =
      std::make_unique<ModuleStatementSyntax>();

  moduleStatement->addModuleKeyword(
      ctx->match(SyntaxKindUtils::SyntaxKind::ModuleKeyword));

  ctx->getCodeFormatterRef()->appendWithSpace();

  moduleStatement->addOpenBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::OpenBracketToken));

  std::unique_ptr<LiteralExpressionSyntax<std::any>> modNameLitExp(
      static_cast<LiteralExpressionSyntax<std::any> *>(
          LiteralExpressionParserUtils::parseExpression(
              ctx, SyntaxKindUtils::SyntaxKind::IdentifierToken)
              .release()));

  moduleStatement->addModuleName(std::move(modNameLitExp));

  moduleStatement->addCloseBracketToken(
      ctx->match(SyntaxKindUtils::SyntaxKind::CloseBracketToken));

  ctx->getCodeFormatterRef()->appendNewLine();

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    ctx->getCodeFormatterRef()->append(
        ctx->getCodeFormatterRef()->getIndentAmount());
    SyntaxKindUtils::SyntaxKind kind = ctx->getKind();

    switch (kind) {
    case SyntaxKindUtils::SyntaxKind::VarKeyword:
    case SyntaxKindUtils::SyntaxKind::ConstKeyword: {

      ctx->setCurrentModuleName(
          moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

      moduleStatement->addStatement(
          VariableParserUtils::parseSingleVariableDeclaration(ctx));

      ctx->setCurrentModuleName("");
      break;
    }
    case SyntaxKindUtils::SyntaxKind::TypeKeyword: {

      ctx->setCurrentModuleName(
          moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

      moduleStatement->addStatement(
          std::make_unique<CustomTypeStatementParser>()->parseStatement(ctx));

      ctx->setCurrentModuleName("");
      break;
    }

    case SyntaxKindUtils::SyntaxKind::ClassKeyword: {

      ctx->setCurrentModuleName(
          moduleStatement->getModuleNameRef()->getTokenPtr()->getText());

      moduleStatement->addStatement(
          std::make_unique<ClassStatementParser>()->parseStatement(ctx));

      ctx->setCurrentModuleName("");
      break;
    }
    case SyntaxKindUtils::SyntaxKind::FunctionKeyword: {

      std::unique_ptr<SyntaxToken<std::any>> functionKeyword = nullptr;

      functionKeyword =
          (ctx->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword));
      ctx->getCodeFormatterRef()->appendWithSpace();

      std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration(
          static_cast<FunctionDeclarationSyntax *>(
              std::make_unique<FunctionDeclarationParser>()
                  ->parseStatement(ctx)
                  .release()));

      functionDeclaration->setFunctionKeyword(std::move(functionKeyword));
      functionDeclaration->setIsMemberFunction(false);

      moduleStatement->addStatement(std::move(functionDeclaration));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
      moduleStatement->addStatement(
          std::make_unique<CallExpressionParser>()->parseExpression(ctx));
      break;
    }

    case SyntaxKindUtils::SyntaxKind::ModuleKeyword: {
      moduleStatement->addStatement(
          std::make_unique<ModuleStatementParser>()->parseStatement(ctx));
      break;
    }
    default: {

      ctx->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken);
      break;
    }
    }
    ctx->getCodeFormatterRef()->appendNewLine();
  }

  return moduleStatement;
}
