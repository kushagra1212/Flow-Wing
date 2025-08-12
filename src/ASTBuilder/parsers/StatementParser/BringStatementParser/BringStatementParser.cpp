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

#include "BringStatementParser.h"
#include "src/ASTBuilder/ASTBuilder.h"
#include "src/ASTBuilder/CodeFormatter/CodeFormatter.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParserFactory.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticHandler/DiagnosticHandler.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticLevel.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticType.h"
#include "src/syntax/CompilationUnitSyntax.h"
#include "src/syntax/SyntaxKindUtils.h"
#include "src/syntax/SyntaxToken.h"
#include "src/syntax/expression/LiteralExpressionSyntax/LiteralExpressionSyntax.h"
#include "src/syntax/statements/BringStatementSyntax/BringStatementSyntax.h"
#include "src/utils/PathUtils.h"
#include "src/utils/Utils.h"

std::unique_ptr<StatementSyntax>
BringStatementParser::parseStatement(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> bringKeyword =
      ctx->match(SyntaxKindUtils::SyntaxKind::BringKeyword);
  ctx->getCodeFormatterRef()->appendWithSpace();
  std::unique_ptr<BringStatementSyntax> bringStatement =
      std::make_unique<BringStatementSyntax>();

  bringStatement->addBringKeyword(std::move(bringKeyword));

  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBraceToken) {
    bringStatement->addOpenBraceToken(
        ctx->match(SyntaxKindUtils::SyntaxKind::OpenBraceToken));
    while (ctx->getKind() != SyntaxKindUtils::SyntaxKind::CloseBraceToken) {
      std::unique_ptr<SyntaxToken<std::any>> identifier =
          ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
      std::string importExpName = identifier->getText();
      bringStatement->addExpression(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(identifier), importExpName));

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::CommaToken) {
        ctx->match(SyntaxKindUtils::SyntaxKind::CommaToken);
        ctx->getCodeFormatterRef()->appendWithSpace();
      }

      if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::EndOfFileToken) {
        ctx->getDiagnosticHandler()->addDiagnostic(
            Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                       DiagnosticUtils::DiagnosticType::Syntactic,
                       {SyntaxKindUtils::to_string(ctx->getKind()),
                        SyntaxKindUtils::to_string(
                            SyntaxKindUtils::SyntaxKind::CloseBraceToken)},
                       Utils::getSourceLocation(ctx->getCurrent()),
                       FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken));
        return bringStatement;
      }
    }
    ctx->match(SyntaxKindUtils::SyntaxKind::CloseBraceToken);
    ctx->getCodeFormatterRef()->appendWithSpace();
  }

  if (bringStatement->getIsChoosyImportPtr()) {
    ctx->match(SyntaxKindUtils::SyntaxKind::FromKeyword);
    ctx->getCodeFormatterRef()->appendWithSpace();
  }
  bool isModule = false;
  std::unique_ptr<SyntaxToken<std::any>> stringToken = nullptr;
  if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
    stringToken = ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);
  } else if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::StringToken) {
    stringToken = ctx->match(SyntaxKindUtils::SyntaxKind::StringToken);
  } else if (ctx->getKind() != SyntaxKindUtils::SyntaxKind::StringToken) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Syntactic,
        {SyntaxKindUtils::to_string(ctx->getKind()),
         SyntaxKindUtils::to_string(SyntaxKindUtils::SyntaxKind::StringToken)},
        Utils::getSourceLocation(ctx->getCurrent()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::UnexpectedToken));
    return bringStatement;
  }

  std::string relativeFilePath = "";

  if (stringToken->getValue().type() == typeid(std::string)) {
    relativeFilePath = std::any_cast<std::string>(stringToken->getValue());

    if (relativeFilePath.find(".fg") == std::string::npos) {

      isModule = true;
      const std::string currentDirPath =
          std::filesystem::path(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath())
              .parent_path()
              .string();

      bringStatement->setModuleName(relativeFilePath);

      std::filesystem::path modulesPath = FlowWing::PathUtils::getModulesPath();

      CODEGEN_DEBUG_LOG("modulesPath", modulesPath);

      std::string moduleFilePath = Utils::findFile(
          modulesPath.string(), relativeFilePath + "-module.fg");

      if (moduleFilePath.empty()) {
        moduleFilePath =
            Utils::findFile(currentDirPath, relativeFilePath + "-module.fg");
      }

      if (moduleFilePath.empty()) {
        ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
            DiagnosticUtils::DiagnosticLevel::Error,
            DiagnosticUtils::DiagnosticType::Syntactic, {relativeFilePath},
            Utils::getSourceLocation(stringToken.get()),
            FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleNotFound));

        return bringStatement;
      }

      DEBUG_LOG("Module File Path: %s", moduleFilePath.c_str());
      relativeFilePath =
          std::filesystem::relative(moduleFilePath, currentDirPath).string();
      stringToken->setValue((relativeFilePath));
    }
    // appendNewLine();
  }
  bringStatement->setIsModuleImport(isModule);

  bringStatement->addPathToken(std::move(stringToken));

  bringStatement->setRelativeFilePath(relativeFilePath);

  std::string absoluteFilePath =
      std::filesystem::path(ctx->getDiagnosticHandler()->getAbsoluteFilePath())
          .parent_path()
          .string() +
      "/" + relativeFilePath;

  std::unique_ptr<FlowWing::DiagnosticHandler> diagnosticHandler =
      std::make_unique<FlowWing::DiagnosticHandler>(absoluteFilePath);

  PARSER_DEBUG_LOG(
      "%d", std::to_string(ctx->getDependencyFileCount(absoluteFilePath)));
  if (ctx->getDependencyFileCount(absoluteFilePath) == 1) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Syntactic, {absoluteFilePath},
        Utils::getSourceLocation(ctx->getCurrent()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::CircularReference));

    SyntaxKindUtils::SyntaxKind currentKind = ctx->getKind();

    if (currentKind == SyntaxKindUtils::SyntaxKind::ExposeKeyword) {
      currentKind = ctx->peek(1)->getKind();
    }

    return StatementParserFactory::createStatementParser(currentKind)
        ->parseStatement(ctx);
  }

  ctx->updateDependencyCount(absoluteFilePath, 1);

  bringStatement->setAbsoluteFilePath(absoluteFilePath);

  ctx->getDiagnosticHandler()->addParentDiagnostics(diagnosticHandler.get());
  bringStatement->setDiagnosticHandler(std::move(diagnosticHandler));

  std::unique_ptr<ASTBuilder> parser = std::make_unique<ASTBuilder>(
      Utils::readLines(absoluteFilePath),
      bringStatement->getDiagnosticHandlerPtr().get(),
      ctx->getDependencyPathsMap());

  std::unique_ptr<CompilationUnitSyntax> compilationUnit =
      parser->createCompilationUnit();

  bringStatement->setCompilationUnit(std::move(compilationUnit));

  ctx->updateDependencyCount(absoluteFilePath, -1);

  return bringStatement;
}
