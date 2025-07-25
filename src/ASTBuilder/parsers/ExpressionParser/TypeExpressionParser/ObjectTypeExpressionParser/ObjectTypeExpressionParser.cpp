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


#include "ObjectTypeExpressionParser.h"

std::unique_ptr<ExpressionSyntax>
ObjectTypeExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<ObjectTypeExpressionSyntax> objectTypeExpression =
      std::make_unique<ObjectTypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE, 0,
              "NBU_OBJECT_TYPE", "NBU_OBJECT_TYPE"));

  std::unique_ptr<SyntaxToken<std::any>> iden =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  std::any value = iden->getValue();

  std::unique_ptr<LiteralExpressionSyntax<std::any>> literalExp =
      std::make_unique<LiteralExpressionSyntax<std::any>>(std::move(iden),
                                                          value);

  objectTypeExpression->setObjectTypeIdentifier(std::move(literalExp));

  return std::move(objectTypeExpression);
}