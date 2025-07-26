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

#include "VariableDeclarationBinder.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundVariableDeclaration/BoundVariableDeclaration.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/common/constants/FlowWingUtilsConstants.h"
#include "src/diagnostics/Diagnostic/Diagnostic.h"
#include "src/diagnostics/Diagnostic/DiagnosticCodeData.h"
#include "src/syntax/statements/VariableDeclarationSyntax/VariableDeclarationSyntax.h"
#include "src/utils/LogConfig.h"

std::unique_ptr<BoundStatement>
VariableDeclarationBinder::bindStatement(SyntaxBinderContext *ctx,
                                         StatementSyntax *statement) {

  VariableDeclarationSyntax *variableDeclaration =
      static_cast<VariableDeclarationSyntax *>(statement);

  std::string variable_str = std::any_cast<std::string>(
      variableDeclaration->getIdentifierRef()->getValue());
  bool isConst = false;

  DEBUG_LOG("Declaring variable " + variable_str);

  if (variableDeclaration->getKeywordRef()) {
    isConst = variableDeclaration->getKeywordRef()->getKind() ==
              SyntaxKindUtils::SyntaxKind::ConstKeyword;
  }

  std::unique_ptr<BoundVariableDeclaration> variable =
      std::make_unique<BoundVariableDeclaration>(
          variableDeclaration->getSourceLocation(), variable_str, isConst,
          variableDeclaration->isExposed());

  if (variableDeclaration->getInoutKeywordRef()) {
    variable->setHasInOutKeyword(true);
  }

  if (variableDeclaration->getAsKeywordRef()) {
    variable->setHasAsKeyword(true);
  }

  variable->setIdentifier(std::make_unique<BoundLiteralExpression<std::any>>(
      variableDeclaration->getIdentifierRef()->getSourceLocation(),
      variableDeclaration->getIdentifierRef()->getValue(),
      variableDeclaration->getIdentifierRef()->getKind()));

  if (variableDeclaration->getTypeRef()) {

    std::unique_ptr<BoundTypeExpression> boundTypeExpression(
        static_cast<BoundTypeExpression *>(
            ExpressionBinderFactory::create(
                variableDeclaration->getTypeRef()->getKind())
                ->bindExpression(ctx, variableDeclaration->getTypeRef().get())
                .release()));

    boundTypeExpression->setVariableNameitBelongsTo(variable_str);
    if (boundTypeExpression->getKind() ==
        BinderKindUtils::BoundObjectTypeExpression) {
      BoundObjectTypeExpression *objectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(boundTypeExpression.get());

      DEBUG_LOG("TNAME " + objectTypeExpression->getTypeName());

      //! This Handles when the Type is Class Type in that Case Since we are
      //! only receiving class Name not the type along with Module name e.g A
      //! not local::A and we are inside the Module local
      //! then we need to add the module prefix to the class name
      //! ModuleName::ClassName {It is statisfied only When we Defining Class}
      //! For Normal Types We are already receiving the ModuleName::TypeName

      if (ctx->getCurrentModuleName() != "" &&
          objectTypeExpression->getTypeName().find(
              FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX) == std::string::npos) {
        objectTypeExpression->getObjectTypeIdentifier()->setValue(
            ctx->getCurrentModuleName() +
            FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
            std::any_cast<std::string>(
                objectTypeExpression->getObjectTypeIdentifier()->getValue()));
      }
      BoundClassStatement *boundClassStatement =
          ctx->getRootRef()->tryGetClass(objectTypeExpression->getTypeName());
      if (boundClassStatement) {
        _className = boundClassStatement->getClassName();
      }
      DEBUG_LOG("CN " + _className);
    }

    variable->setTypeExpression(std::move(boundTypeExpression));
  }
  if (variableDeclaration->getHasNewKeyWord())
    variable->setMemoryKind(BinderKindUtils::MemoryKind::Heap);
  variable->setClassItBelongsTo(_className);

  if (variableDeclaration->getInitializerRef()) {
    std::unique_ptr<BoundExpression> boundInitializerExpression =
        std::move(ExpressionBinderFactory::create(
                      variableDeclaration->getInitializerRef()->getKind())
                      ->bindExpression(
                          ctx, variableDeclaration->getInitializerRef().get()));

    variable->setInitializer(std::move(boundInitializerExpression));
  }

  if (!ctx->getRootRef()->tryDeclareVariable(variable_str, variable.get())) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic, {variable_str},
        Utils::getSourceLocation(variableDeclaration->getIdentifierRef().get()),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::VariableAlreadyDeclared));
  }

  return std::move(variable);
}

void VariableDeclarationBinder::setClassName(const std::string &className) {
  _className = className;
}