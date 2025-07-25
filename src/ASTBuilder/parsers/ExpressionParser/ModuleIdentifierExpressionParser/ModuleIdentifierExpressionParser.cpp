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


#include "ModuleIdentifierExpressionParser.h"
#include <memory>

std::unique_ptr<ExpressionSyntax>
ModuleIdentifierExpressionParser::parseExpression(ParserContext *ctx) {
  std::unique_ptr<SyntaxToken<std::any>> moduleIdentifier =
      std::move(ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken));

  ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
  ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);

  std::unique_ptr<ExpressionSyntax> member = std::move(
      std::make_unique<IdentifierExpressionParser>()->parseExpression(ctx));

  std::unique_ptr<TypeExpressionSyntax> typeExpression =
      std::make_unique<TypeExpressionSyntax>(
          std::make_unique<SyntaxToken<std::any>>(
              ctx->getDiagnosticHandler()->getAbsoluteFilePath(), 0,
              SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE, 0,
              "NBU_UNKNOWN_TYPE", "NBU_UNKNOWN_TYPE"));

  std::any value = moduleIdentifier->getValue();

  std::unique_ptr<VariableExpressionSyntax> variExp =
      std::make_unique<VariableExpressionSyntax>(
          std::make_unique<LiteralExpressionSyntax<std::any>>(
              std::move(moduleIdentifier), value),
          false, std::move(typeExpression));
  const std::string PREFIX = std::any_cast<std::string>(value) +
                             FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX;

  if (member->getKind() ==
      SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax) {

    VariableExpressionSyntax *memberExp =
        static_cast<VariableExpressionSyntax *>(member.get());
    memberExp->getIdentifierTokenRef()->setValue(
        PREFIX + (memberExp->getVariableName()));
    memberExp->getIdentifierTokenRef()->setText(std::any_cast<std::string>(
        memberExp->getIdentifierTokenRef()->getValue()));
  } else if (member->getKind() ==
             SyntaxKindUtils::SyntaxKind::AssignmentExpression) {

    AssignmentExpressionSyntax *assignExpr =
        static_cast<AssignmentExpressionSyntax *>(member.get());

    if (assignExpr->getLeftRef()->getKind() ==
        SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax) {

      VariableExpressionSyntax *memberExp =
          static_cast<VariableExpressionSyntax *>(
              assignExpr->getLeftRef().get());
      memberExp->getIdentifierTokenRef()->setValue(
          PREFIX + (memberExp->getVariableName()));
      memberExp->getIdentifierTokenRef()->setText(std::any_cast<std::string>(
          memberExp->getIdentifierTokenRef()->getValue()));

    } else if (assignExpr->getLeftRef()->getKind() ==
               SyntaxKindUtils::SyntaxKind::IndexExpression) {
      IndexExpressionSyntax *memberExp =
          static_cast<IndexExpressionSyntax *>(assignExpr->getLeftRef().get());
      //! TODO:
      memberExp->getIndexIdentifierExpressionRef()->setValue(
          PREFIX +
          std::any_cast<std::string>(
              memberExp->getIndexIdentifierExpressionRef()->getValue()));
      memberExp->getIndexIdentifierExpressionRef()->setText(
          std::any_cast<std::string>(
              memberExp->getIndexIdentifierExpressionRef()->getValue()));
    }
  } else if (member->getKind() == SyntaxKindUtils::SyntaxKind::CallExpression) {

    CallExpressionSyntax *callExp =
        static_cast<CallExpressionSyntax *>(member.get());

    callExp->getIdentifierPtr()->setValue(
        PREFIX +
        std::any_cast<std::string>((callExp->getIdentifierPtr()->getValue())));

    callExp->getIdentifierPtr()->setText(
        std::any_cast<std::string>(callExp->getIdentifierPtr()->getValue()));
  }

  variExp->setModuleNameorCallExpression(std::move(member));

  return std::move(variExp);
}