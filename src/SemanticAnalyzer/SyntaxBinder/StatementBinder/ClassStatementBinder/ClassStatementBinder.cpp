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

#include "ClassStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundClassStatement/BoundClassStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/MemberBinder/FunctionDeclarationBinder/FunctionDeclarationBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/VariableDeclarationBinder/VariableDeclarationBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticLevel.h"
#include "src/diagnostics/DiagnosticUtils/DiagnosticType.h"
#include "src/syntax/statements/ClassStatementSyntax/ClassStatementSyntax.h"

std::unique_ptr<BoundStatement>
ClassStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {

  ClassStatementSyntax *classStatement =
      static_cast<ClassStatementSyntax *>(statement);

  const std::string CURRENT_MODULE_NAME = ctx->getCurrentModuleName();

  ctx->setCurrentModuleName("");

  ctx->insertScope();

  std::unique_ptr<BoundClassStatement> boundClassStat =
      std::make_unique<BoundClassStatement>(
          classStatement->getSourceLocation());

  std::string className = std::any_cast<std::string>(
      classStatement->getClassNameIdentifierRef()->getValue());

  ctx->getRootRef()->setClassName(className);
  boundClassStat->setClassName(className);

  if (classStatement->getExposeKeywordRef()) {
    boundClassStat->setIsExposed(true);
  }

  // If It Has Parent

  if (classStatement->getParentClassNameIdentifierRef()) {
    std::string parentClassName = std::any_cast<std::string>(
        classStatement->getParentClassNameIdentifierRef()->getValue());
    BoundClassStatement *parentClassStat =
        ctx->getRootRef()->tryGetClass(parentClassName);

    if (!parentClassStat) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          {parentClassName, boundClassStat->getClassName()},
          classStatement->getParentClassNameIdentifierRef()
              ->getSourceLocation(),
          FLOW_WING::DIAGNOSTIC::DiagnosticCode::ParentClassNotFound));

      return std::move(boundClassStat);
    }

    boundClassStat->setParentClass(parentClassStat);
    boundClassStat->setParentClassName(parentClassName);

    for (auto &var : parentClassStat->getAllMemberVariablesRef()) {
      boundClassStat->addMemberVariablePtr(var);
    }

    for (auto &func : parentClassStat->getAllFunctionNamesRef()) {
      boundClassStat->addFunctionName(func);
    }
  }

  // Class ItsSelf
  for (auto &cusType : classStatement->getCustomTypeStatementsRef()) {
    //! Mutating The Custom Type typeName to className +
    //! FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX
    // std::string typeName =
    //     std::any_cast<std::string>(cusType->getTypeNameRef()->getValue()) +
    //     FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
    //     IDGenerator::CustomTypeIDGenerator::instance()->nextString();

    // cusType->setTypeNameString(typeName);

    boundClassStat->addCustomType(
        (StatementBinderFactory::create(cusType->getKind())
             ->bindStatement(ctx, cusType.get())));
  }

  std::unordered_map<std::string, int> varMemberMap;

  for (auto &var : classStatement->getDataMembersRef()) {
    std::unique_ptr<VariableDeclarationBinder> varBinder =
        std::make_unique<VariableDeclarationBinder>();

    varBinder->setClassName(boundClassStat->getClassName());

    std::unique_ptr<BoundVariableDeclaration> boundMemberVariable(
        static_cast<BoundVariableDeclaration *>(
            varBinder->bindStatement(ctx, var.get()).release()));

    boundClassStat->addMemberVariablePtr(boundMemberVariable.get());

    varMemberMap[boundMemberVariable->getVariableName()] = 1;

    boundClassStat->addMemberVariable(std::move(boundMemberVariable));
  }

  for (auto &var : boundClassStat->getAllMemberVariablesRef()) {
    boundClassStat->addKeyTypePair(var->getIdentifierRef().get(),
                                   (var->getTypeExpression().get()));
    ctx->getRootRef()->tryDeclareVariable("self." + var->getVariableName(),
                                          var);
    if (!varMemberMap[var->getVariableName()]) {
      ctx->getRootRef()->tryDeclareVariable(var->getVariableName(), var);
    }
  }

  ctx->insertScope();

  if (!ctx->getRootRef()->tryDeclareClass(boundClassStat.get())) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        {boundClassStat->getClassName()}, boundClassStat->getLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassAlreadyDeclared));
  }

  auto funBinder = std::make_unique<FunctionDeclarationBinder>();

  for (const auto &fun : classStatement->getClassMemberFunctionsRef()) {
    fun->setIsOnlyDeclared(true);

    boundClassStat->addFunctionName(
        std::any_cast<std::string>(fun->getIdentifierTokenPtr()->getValue()));

    funBinder->setPrefix(className +
                         FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX);

    boundClassStat->addMemberFunction((funBinder->bindMember(ctx, fun.get())));
  }

  for (const auto &fun : classStatement->getClassMemberFunctionsRef()) {
    fun->setIsOnlyDeclared(false);

    funBinder->setPrefix(className +
                         FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX);

    boundClassStat->addMemberFunction((funBinder->bindMember(ctx, fun.get())));
  }

  ctx->removeScope();

  ctx->removeScope();

  if (CURRENT_MODULE_NAME != "") {
    if (!ctx->getRootRef()->tryDeclareClassGlobal(boundClassStat.get())) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          {boundClassStat->getClassName()}, boundClassStat->getLocation(),
          FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassAlreadyDeclared));
    }
  } else {
    if (!ctx->getRootRef()->tryDeclareClass(boundClassStat.get())) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          {boundClassStat->getClassName()}, boundClassStat->getLocation(),
          FLOW_WING::DIAGNOSTIC::DiagnosticCode::ClassAlreadyDeclared));
    }
  }

  return std::move(boundClassStat);
}