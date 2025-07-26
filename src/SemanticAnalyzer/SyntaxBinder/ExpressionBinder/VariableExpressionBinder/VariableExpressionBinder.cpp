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

#include "VariableExpressionBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundIndexExpression/BoundIndexExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundVariableExpression/BoundVariableExpression.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/expression/CallExpressionSyntax/CallExpressionSyntax.h"
#include "src/syntax/expression/IndexExpressionSyntax/IndexExpressionSyntax.h"
#include "src/syntax/expression/VariableExpressionSyntax/VariableExpressionSyntax.h"
#include "src/utils/LogConfig.h"

std::unique_ptr<BoundExpression>
VariableExpressionBinder::bindExpression(SyntaxBinderContext *ctx,
                                         ExpressionSyntax *expression) {

  VariableExpressionSyntax *variableExpressionSyntax =
      static_cast<VariableExpressionSyntax *>(expression);

  DEBUG_LOG("Checking out variable " +
            variableExpressionSyntax->getVariableName());

  BoundVariableDeclaration *variable = ctx->getRootRef()->tryGetVariable(
      variableExpressionSyntax->getVariableName());

  if (variableExpressionSyntax->hasModuleNameorCallExpression()) {
    BoundModuleStatement *module = ctx->getRootRef()->tryGetModule(
        variableExpressionSyntax->getVariableName());

    if (!module) {
      ctx->getDiagnosticHandler()->addDiagnostic(
          Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                     DiagnosticUtils::DiagnosticType::Semantic,
                     {variableExpressionSyntax->getVariableName()},
                     variableExpressionSyntax->getSourceLocation(),
                     FLOW_WING::DIAGNOSTIC::DiagnosticCode::ModuleNotFound));
      return nullptr;
    }
    return ExpressionBinderFactory::create(
               variableExpressionSyntax->getModuleNameorCallExpression()
                   ->getKind())
        ->bindExpression(
            ctx,
            variableExpressionSyntax->getModuleNameorCallExpression().get());
  }

  if (variableExpressionSyntax->getVariableName() == "self") {

    std::unique_ptr<BoundLiteralExpression<std::any>> bLit(
        static_cast<BoundLiteralExpression<std::any> *>(
            ExpressionBinderFactory::create(
                variableExpressionSyntax->getIdentifierTokenRef()->getKind())
                ->bindExpression(
                    ctx,
                    variableExpressionSyntax->getIdentifierTokenRef().get())
                .release()));

    std::unique_ptr<BoundVariableExpression> boundVariableExpression =
        std::make_unique<BoundVariableExpression>(
            variableExpressionSyntax->getSourceLocation(), std::move(bLit),
            variableExpressionSyntax->isConstant(), nullptr);
    boundVariableExpression->setSelf(variableExpressionSyntax->getIsSelf());
    boundVariableExpression->setHasNewKeyword(
        variableExpressionSyntax->getHasNewKeyword());
    return std::move(boundVariableExpression);
  }

  auto func = ctx->getRootRef()->tryGetFunction(
      variableExpressionSyntax->getVariableName());

  if (!variable && variableExpressionSyntax->getVariableName() != "self" &&
      !func) {

    ctx->getDiagnosticHandler()->addDiagnostic(
        Diagnostic(DiagnosticUtils::DiagnosticLevel::Error,
                   DiagnosticUtils::DiagnosticType::Semantic,
                   {variableExpressionSyntax->getVariableName()},
                   variableExpressionSyntax->getSourceLocation(),
                   FLOW_WING::DIAGNOSTIC::DiagnosticCode::VariableNotFound));
    return nullptr;
  }

  if (variable && variable->getTypeExpression().get()->getKind() ==
                      BinderKindUtils::BoundObjectExpression) {
    BoundObjectTypeExpression *boundObjTypeExp =
        static_cast<BoundObjectTypeExpression *>(
            variable->getTypeExpression().get());

    BoundCustomTypeStatement *boundCustomType =
        ctx->getRootRef()->tryGetCustomType(boundObjTypeExp->getTypeName());

    std::unordered_map<std::string, int8_t> boundAttributes;

    for (const auto &[bLE, bTE] : boundCustomType->getKeyPairs()) {
      boundAttributes[std::any_cast<std::string>(bLE->getValue())] = 1;
    }
  }

  BoundTypeExpression *typeExpr = nullptr;
  if (variable) {
    typeExpr = variable->getTypeExpression().get();
  } else {
    typeExpr = func->getFunctionTypeRef().get();
  }

  std::unique_ptr<BoundLiteralExpression<std::any>> bLit(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              variableExpressionSyntax->getIdentifierTokenRef()->getKind())
              ->bindExpression(
                  ctx, variableExpressionSyntax->getIdentifierTokenRef().get())
              .release()));

  std::unique_ptr<BoundVariableExpression> boundVariableExpression =
      std::make_unique<BoundVariableExpression>(
          variableExpressionSyntax->getSourceLocation(), std::move(bLit),
          variableExpressionSyntax->isConstant(), typeExpr);

  boundVariableExpression->setSelf(variableExpressionSyntax->getIsSelf());
  boundVariableExpression->setHasNewKeyword(
      variableExpressionSyntax->getHasNewKeyword());
  std::string classNameVariableBelongsTo = "";
  if (variable) {
    classNameVariableBelongsTo = variable->getClassItBelongsTo();
  }
  uint64_t index = 0;
  for (const auto &dotExpression :
       variableExpressionSyntax->getDotExpressionList()) {
    if (dotExpression->getKind() ==
        SyntaxKindUtils::SyntaxKind::IndexExpression) {

      IndexExpressionSyntax *indexExpression =
          static_cast<IndexExpressionSyntax *>(dotExpression.get());
      std::unique_ptr<BoundLiteralExpression<std::any>>
          localBoundIdentifierExpression(
              (BoundLiteralExpression<std::any> *)
                  ExpressionBinderFactory::create(
                      indexExpression->getIndexIdentifierExpressionRef()
                          ->getKind())
                      ->bindExpression(
                          ctx,
                          indexExpression->getIndexIdentifierExpressionRef()
                              .get())
                      .release());

      std::unique_ptr<BoundIndexExpression> localBoundIndexExp =
          std::make_unique<BoundIndexExpression>(
              indexExpression->getSourceLocation(),
              std::move(localBoundIdentifierExpression));

      for (const auto &indexExp : indexExpression->getIndexExpressionsRef()) {
        localBoundIndexExp->addBoundIndexExpression(
            std::move(ExpressionBinderFactory::create(indexExp->getKind())
                          ->bindExpression(ctx, indexExp.get())));
      }
      boundVariableExpression->addDotExpression(std::move(localBoundIndexExp));
    } else {
      if (dotExpression->getKind() ==
          SyntaxKindUtils::SyntaxKind::CallExpression) {
        CallExpressionSyntax *callExpression =
            static_cast<CallExpressionSyntax *>(dotExpression.get());

        if (!classNameVariableBelongsTo.empty()) {
          std::any fName = variable->getClassItBelongsTo() +
                           FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX +
                           std::any_cast<std::string>(
                               callExpression->getIdentifierPtr()->getValue());

          callExpression->getIdentifierPtr()->setValue((fName));
        }

        boundVariableExpression->addDotExpression(
            std::move(ExpressionBinderFactory::create(callExpression->getKind())
                          ->bindExpression(ctx, callExpression)));
      } else {
        std::unique_ptr<BoundExpression> localBoundExpression =
            std::move(ExpressionBinderFactory::create(dotExpression->getKind())
                          ->bindExpression(ctx, dotExpression.get()));

        if (!classNameVariableBelongsTo.empty()) {
          BoundClassStatement *boundClassStatement =
              ctx->getRootRef()->tryGetClass(classNameVariableBelongsTo);
          if (boundClassStatement) {
            for (auto &_variable :
                 boundClassStatement->getAllMemberVariablesRef()) {

              if (_variable && _variable->getTypeExpression() &&
                  _variable->getTypeExpression()->getKind() ==
                      BinderKindUtils::BoundNodeKind::
                          BoundObjectTypeExpression) {
                BoundObjectTypeExpression *boundObjTypeExp =
                    static_cast<BoundObjectTypeExpression *>(
                        _variable->getTypeExpression().get());

                BoundClassStatement *nestedBoundClassStatement =
                    ctx->getRootRef()->tryGetClass(Utils::getActualTypeName(
                        boundObjTypeExp->getTypeName()));

                if (nestedBoundClassStatement) {
                  classNameVariableBelongsTo =
                      nestedBoundClassStatement->getClassName();
                }
              }
            }
          }
        }
        boundVariableExpression->addDotExpression(
            std::move(ExpressionBinderFactory::create(dotExpression->getKind())
                          ->bindExpression(ctx, dotExpression.get())));
      }
    }
    DEBUG_LOG("classNameVariableBelongsTo: ", classNameVariableBelongsTo);
    if (index != 0) {
      classNameVariableBelongsTo = "";
    }
    index++;
  }

  return std::move(boundVariableExpression);
}