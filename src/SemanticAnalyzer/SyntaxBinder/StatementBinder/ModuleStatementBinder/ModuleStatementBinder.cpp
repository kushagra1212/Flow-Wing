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

#include "ModuleStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundModuleStatement/BoundModuleStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/MemberBinder/FunctionDeclarationBinder/FunctionDeclarationBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/VariableDeclarationBinder/VariableDeclarationBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"
#include "src/syntax/statements/CustomTypeStatementSyntax/CustomTypeStatementSyntax.h"
#include "src/syntax/statements/ModuleStatementSyntax/ModuleStatementSyntax.h"
#include <memory>

std::unique_ptr<BoundStatement>
ModuleStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                     StatementSyntax *statement) {

  ModuleStatementSyntax *moduleStatement =
      static_cast<ModuleStatementSyntax *>(statement);

  std::unique_ptr<BoundModuleStatement> boundModuleStat =
      std::make_unique<BoundModuleStatement>(
          moduleStatement->getSourceLocation());

  std::unique_ptr<BoundLiteralExpression<std::any>> moduleNameIdef(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              moduleStatement->getModuleNameRef()->getKind())
              ->bindExpression(ctx, moduleStatement->getModuleNameRef().get())
              .release()));

  boundModuleStat->addModuleNameIdentifier(std::move(moduleNameIdef));

  ctx->setCurrentModuleName(boundModuleStat->getModuleName());

  ctx->getRootRef()->tryDeclareModuleGlobal(boundModuleStat.get());

  for (auto &stat : moduleStatement->getStatementsRef()) {

    ctx->setCurrentModuleName(boundModuleStat->getModuleName());

    switch (stat->getKind()) {
    case SyntaxKindUtils::SyntaxKind::CustomTypeStatement: {
      CustomTypeStatementSyntax *customTypeStatement =
          static_cast<CustomTypeStatementSyntax *>(stat.get());

      boundModuleStat->addCustomTypeStatement(std::move(
          StatementBinderFactory::create(customTypeStatement->getKind())
              ->bindStatement(ctx, customTypeStatement)));

      break;
    }
    case SyntaxKindUtils::SyntaxKind::ClassStatement: {
      ClassStatementSyntax *classStatement =
          static_cast<ClassStatementSyntax *>(stat.get());

      boundModuleStat->addClassStatement(
          std::move(StatementBinderFactory::create(classStatement->getKind())
                        ->bindStatement(ctx, classStatement)));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::VariableDeclaration: {
      VariableDeclarationSyntax *var =
          static_cast<VariableDeclarationSyntax *>(stat.get());

      std::unique_ptr<VariableDeclarationBinder> varBinder =
          std::make_unique<VariableDeclarationBinder>();

      varBinder->setClassName(boundModuleStat->getModuleName());

      std::unique_ptr<BoundVariableDeclaration> boundMemberVariable(
          static_cast<BoundVariableDeclaration *>(
              varBinder->bindStatement(ctx, var).release()));

      ctx->getRootRef()->tryDeclareVariableGlobal(
          boundMemberVariable->getVariableName(), boundMemberVariable.get());

      boundModuleStat->addVariableStatement(std::move(boundMemberVariable));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax: {
      FunctionDeclarationSyntax *fun =
          static_cast<FunctionDeclarationSyntax *>(stat.get());

      std::unique_ptr<FunctionDeclarationBinder> funBinder =
          std::make_unique<FunctionDeclarationBinder>();

      if (fun->isOnlyDeclared()) {
        funBinder->setPrefix("");
        boundModuleStat->addFunctionStatement(funBinder->bindMember(ctx, fun));

        break;
      }

      funBinder->setPrefix(boundModuleStat->getModuleName() +
                           FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX);
      fun->setIsOnlyDeclared(true);

      boundModuleStat->addFunctionStatement(funBinder->bindMember(ctx, fun));

      // Define Functions
      fun->setIsOnlyDeclared(false);
      break;
    }
    case SyntaxKindUtils::SyntaxKind::CallExpression: {
      CallExpressionSyntax *call =
          static_cast<CallExpressionSyntax *>(stat.get());

      boundModuleStat->addCallerExpression(
          std::move(ExpressionBinderFactory::create(stat->getKind())
                        ->bindExpression(ctx, call)));
      break;
    }
    case SyntaxKindUtils::SyntaxKind::ModuleStatement: {

      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          {ctx->getCurrentModuleName()}, stat->getSourceLocation(),
          FLOW_WING::DIAGNOSTIC::DiagnosticCode::DuplicateModuleDeclaration));

      break;
    }
    default: {
      //? This error will never be thrown because the parser will not allow
      ctx->getDiagnosticHandler()->addDiagnostic(
          Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     {ctx->getCurrentModuleName()}, stat->getSourceLocation(),
                     FLOW_WING::DIAGNOSTIC::DiagnosticCode::
                         UnsupportedExpressionOrStatementInModule));

      break;
    }
    }
  }

  for (auto &stat : moduleStatement->getStatementsRef()) {
    if (stat->getKind() ==
        SyntaxKindUtils::SyntaxKind::FunctionDeclarationSyntax) {
      FunctionDeclarationSyntax *fun =
          static_cast<FunctionDeclarationSyntax *>(stat.get());
      if (fun->isOnlyDeclared()) {
        continue;
      }

      ctx->setCurrentModuleName(boundModuleStat->getModuleName());

      std::unique_ptr<FunctionDeclarationBinder> funBinder =
          std::make_unique<FunctionDeclarationBinder>();

      funBinder->setPrefix(boundModuleStat->getModuleName() +
                           FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX);

      boundModuleStat->addFunctionStatement(
          std::move(funBinder->bindMember(ctx, fun)));
    }
  }

  ctx->setCurrentModuleName("");

  return std::move(boundModuleStat);
}