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

#include "TypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/ArrayTypeExpressionParser/ArrayTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/FunctionTypeExpressionParser/FunctionTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/ModuleAccessTypeExpressionParser/ModuleAccessTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/ObjectTypeExpressionParser/ObjectTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TypeExpressionParser/PrimitiveTypeExpressionParser/PrimitiveTypeExpressionParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/expression/IdentifierExpressionSyntax/IdentifierExpressionSyntax.h"
#include "src/syntax/expression/TypeExpressionSyntax/ObjectTypeExpressionSyntax/ObjectTypeExpressionSyntax.h"
#include <memory>

namespace flow_wing {
namespace parser {

TypeExpressionParser::TypeExpressionParser(ParserContext *ctx) : m_ctx(ctx) {}

std::unique_ptr<syntax::ExpressionSyntax> TypeExpressionParser::parse() {

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kOpenBracketToken) {
    return std::make_unique<parser::FunctionTypeExpressionParser>(m_ctx)
        ->parse();
  }

  auto type_expression =
      std::make_unique<parser::PrimitiveTypeExpressionParser>(m_ctx)->parse();

  if (type_expression == nullptr) {
    auto identifier_expression =
        std::make_unique<syntax::IdentifierExpressionSyntax>(
            m_ctx->match(lexer::TokenKind::kIdentifierToken)); // identifier

    if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kColonColonToken) {
      return std::make_unique<ModuleAccessTypeExpressionParser>(m_ctx)
          ->parsePostfix(std::move(identifier_expression));
    }

    type_expression =
        std::make_unique<parser::ObjectTypeExpressionParser>(m_ctx)
            ->parsePostfix(std::move(identifier_expression));
  }

  if (m_ctx->getCurrentTokenKind() == lexer::TokenKind::kOpenBracketToken) {
    type_expression =
        std::make_unique<parser::ArrayTypeExpressionParser>(m_ctx)
            ->parsePostfix(
                std::move(type_expression)); // int[2][3] or objectType[2][3]
  }

  return type_expression;
}

} // namespace parser
} // namespace flow_wing

// std::unique_ptr<syntax::ExpressionSyntax>
// TypeExpressionParser::parseExpression(ParserContext *ctx) {

//   if (ctx->peek(1)->getKind() ==
//           SyntaxKindUtils::SyntaxKind::OpenBracketToken ||
//       (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken &&
//        ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
//        ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
//        ctx->peek(4)->getKind() ==
//            SyntaxKindUtils::SyntaxKind::OpenBracketToken)) {
//     return
//     std::make_unique<ArrayTypeExpressionParser>()->parseExpression(ctx);
//   }

//   if (ctx->peek(1)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken &&
//       ctx->peek(2)->getKind() == SyntaxKindUtils::SyntaxKind::ColonToken) {
//     std::unique_ptr<SyntaxToken<std::any>> iden =
//         ctx->match(SyntaxKindUtils::SyntaxKind::IdentifierToken);

//     ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);
//     ctx->match(SyntaxKindUtils::SyntaxKind::ColonToken);

//     std::unique_ptr<ObjectTypeExpressionSyntax> objectType(
//         static_cast<ObjectTypeExpressionSyntax *>(
//             std::make_unique<ObjectTypeExpressionParser>()
//                 ->parseExpression(ctx)
//                 .release()));

//     objectType->getObjectTypeIdentifierRef()->getTokenPtr()->setValue(
//         std::any_cast<std::string>(iden->getValue()) +
//         FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
//         std::any_cast<std::string>(objectType->getObjectTypeIdentifierRef()
//                                        ->getTokenPtr()
//                                        ->getValue()));
//     objectType->getObjectTypeIdentifierRef()->getTokenPtr()->setText(
//         (iden->getText()) + FLOWWING::UTILS::CONSTANTS::MODULE_PREFIX +
//         (objectType->getObjectTypeIdentifierRef()->getTokenPtr()->getText()));

//     return objectType;
//   }

//   if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::OpenBracketToken &&
//       ctx->peek(1)->getKind() ==
//           SyntaxKindUtils::SyntaxKind::OpenParenthesisToken) {
//     return std::make_unique<FunctionTypeExpressionParser>()->parseExpression(
//         ctx);
//   }

//   if (ctx->getKind() == SyntaxKindUtils::SyntaxKind::IdentifierToken) {
//     return
//     std::make_unique<ObjectTypeExpressionParser>()->parseExpression(ctx);
//   }

//   return std::make_unique<TypeExpressionSyntax>(
//       std::make_unique<PrimitiveTypeExpressionParser>()->parseExpression(ctx));
// }