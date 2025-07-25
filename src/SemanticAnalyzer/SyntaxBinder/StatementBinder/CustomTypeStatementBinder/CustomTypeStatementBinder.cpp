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



#include "CustomTypeStatementBinder.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

std::unique_ptr<BoundStatement>
CustomTypeStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                         StatementSyntax *statement) {

  CustomTypeStatementSyntax *customTypeStatement =
      static_cast<CustomTypeStatementSyntax *>(statement);

  std::unique_ptr<BoundCustomTypeStatement> boundCustomTypeStatement =
      std::make_unique<BoundCustomTypeStatement>(
          customTypeStatement->getSourceLocation(),
          customTypeStatement->isExposed());

  std::unique_ptr<BoundLiteralExpression<std::any>> boundLiteralExpression(
      static_cast<BoundLiteralExpression<std::any> *>(
          ExpressionBinderFactory::create(
              customTypeStatement->getTypeNameRef()->getKind())
              ->bindExpression(ctx, customTypeStatement->getTypeNameRef().get())
              .release()));

  boundCustomTypeStatement->setTypeName(std::move(boundLiteralExpression));

  std::unordered_map<std::string, int8_t> attributes;

  for (int i = 0; i < customTypeStatement->getKeyTypePairsRef().size(); i++) {
    const std::string &key = customTypeStatement->getKeyTypePairsRef()[i]
                                 ->getKey()
                                 ->getTokenPtr()
                                 ->getText();

    if (attributes.find(key) != attributes.end()) {
      ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
          DiagnosticUtils::DiagnosticLevel::Error,
          DiagnosticUtils::DiagnosticType::Semantic,
          {key, Utils::getActualTypeName(
                    boundCustomTypeStatement->getTypeNameAsString())},
          customTypeStatement->getKeyTypePairsRef()[i]
              ->getKey()
              ->getSourceLocation(),
          FLOW_WING::DIAGNOSTIC::DiagnosticCode::
              DuplicateAttributeKeyInCustomType));

      return std::move(boundCustomTypeStatement);
    }
    attributes[key] = 1;

    std::unique_ptr<BoundLiteralExpression<std::any>> boundLiteralExpression(
        static_cast<BoundLiteralExpression<std::any> *>(
            ExpressionBinderFactory::create(
                customTypeStatement->getKeyTypePairsRef()[i]
                    ->getKey()
                    ->getKind())
                ->bindExpression(ctx,
                                 customTypeStatement->getKeyTypePairsRef()[i]
                                     ->getKey()
                                     .get())
                .release()));

    std::unique_ptr<BoundTypeExpression> boundTypeExpression(
        static_cast<BoundTypeExpression *>(
            ExpressionBinderFactory::create(
                customTypeStatement->getKeyTypePairsRef()[i]
                    ->getValue()
                    ->getKind())
                ->bindExpression(ctx,
                                 customTypeStatement->getKeyTypePairsRef()[i]
                                     ->getValue()
                                     .get())
                .release()));

    boundCustomTypeStatement->addKeyTypePair(std::move(boundLiteralExpression),
                                             std::move(boundTypeExpression));
  }

  if (ctx->getCurrentModuleName() != "" &&
      !ctx->getRootRef()->tryDeclareCustomTypeGlobal(
          boundCustomTypeStatement.get())) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        {Utils::getActualTypeName(
            boundCustomTypeStatement->getTypeNameAsString())},
        customTypeStatement->getTypeNameRef()->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::DuplicateCustomTypeDeclaration));
  }
  if (ctx->getCurrentModuleName() == "" &&
      !ctx->getRootRef()->tryDeclareCustomType(
          boundCustomTypeStatement.get())) {
    ctx->getDiagnosticHandler()->addDiagnostic(Diagnostic(
        DiagnosticUtils::DiagnosticLevel::Error,
        DiagnosticUtils::DiagnosticType::Semantic,
        {Utils::getActualTypeName(
            boundCustomTypeStatement->getTypeNameAsString())},
        customTypeStatement->getTypeNameRef()->getSourceLocation(),
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::DuplicateCustomTypeDeclaration));
  }

  return std::move(boundCustomTypeStatement);
}