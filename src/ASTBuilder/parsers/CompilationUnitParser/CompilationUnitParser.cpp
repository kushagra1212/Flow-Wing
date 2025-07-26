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

#include "CompilationUnitParser.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/FunctionDeclarationParser/FunctionDeclarationParser.h"
#include "src/ASTBuilder/parsers/StatementParser/GlobalStatementParser/GlobalStatementParser.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include <memory>

std::unique_ptr<MemberSyntax>
CompilationUnitParser::parseMember(ParserContext *ctx) {
  SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

  if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
    currentKind = ctx->peek(1)->getKind();
  }

  if (currentKind == SyntaxKindUtils::SyntaxKind::FunctionKeyword) {
    ctx->getCodeFormatterRef()->appendNewLine();

    std::unique_ptr<SyntaxToken<std::any>> exposedKeyword = nullptr,
                                           functionKeyword = nullptr;
    if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
      exposedKeyword =
          std::move(ctx->match(SyntaxKindUtils::SyntaxKind::ExposeKeyword));

      ctx->getCodeFormatterRef()->appendWithSpace();
    }

    functionKeyword =
        (std::move(ctx->match(SyntaxKindUtils::SyntaxKind::FunctionKeyword)));
    ctx->getCodeFormatterRef()->appendWithSpace();

    std::unique_ptr<FunctionDeclarationSyntax> functionDeclaration(
        static_cast<FunctionDeclarationSyntax *>(
            std::make_unique<FunctionDeclarationParser>()
                ->parseStatement(ctx)
                .release()));

    functionDeclaration->setExposedKeyword(std::move(exposedKeyword));
    functionDeclaration->setFunctionKeyword(std::move(functionKeyword));
    functionDeclaration->setIsMemberFunction(false);

    return std::move(functionDeclaration);
  }

  return std::make_unique<GlobalStatementParser>()->parseStatement(ctx);
}

std::unique_ptr<CompilationUnitSyntax>
CompilationUnitParser::parseCompilationUnit(ParserContext *ctx) {
  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      std::make_unique<CompilationUnitSyntax>();

  while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::EndOfFileToken) {

    compilationUnit->addMember(std::move(parseMember(ctx)));
  }

  std::unique_ptr<SyntaxToken<std::any>> endOfFileToken =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::EndOfFileToken));

  compilationUnit->setEndOfFileToken(std::move(endOfFileToken));

  return std::move(compilationUnit);
}