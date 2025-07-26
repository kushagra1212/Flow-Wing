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

#include "PrimaryExpressionParserFactory.h"
#include "src/ASTBuilder/parsers/ExpressionParser/BracketedExpressionParser/BracketedExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/CallExpressionParser/CallExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/CharacterExpressionParser/CharacterExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/CommaExpressionParser/CommaExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/DefaultPrimaryExpressionParser/DefaultPrimaryExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/FalseExpressionParser/FalseExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/IdentifierExpressionParser/IdentifierExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/NirastExpressionParser/NirastExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/NumberExpressionParser/NumberExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ObjectExpressionParser/ObjectExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/ParenthesizedExpressionParser/ParenthesizedExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/StringExpressionParser/StringExpressionParser.h"
#include "src/ASTBuilder/parsers/ExpressionParser/TrueExpressionParser/TrueExpressionParser.h"
#include "src/syntax/SyntaxKindUtils.h"
#include <cassert>

std::unique_ptr<ExpressionParser>
PrimaryExpressionParserFactory::createPrimaryExpressionParser(
    const SyntaxKindUtils::SyntaxKind &kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::OpenParenthesisToken: {
    return std::make_unique<ParenthesizedExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::NumberToken: {
    return std::make_unique<NumberExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::StringToken: {
    return std::make_unique<StringExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::CharacterToken: {
    return std::make_unique<CharacterExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::TrueKeyword: {
    return std::make_unique<TrueExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::NirastKeyword: {
    return std::make_unique<NirastExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::FalseKeyword: {
    return std::make_unique<FalseExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::CommaToken: {
    return std::make_unique<CommaExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::NewKeyword: {
    return std::make_unique<CallExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::IdentifierToken: {
    return std::make_unique<IdentifierExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::OpenBracketToken: {
    return std::make_unique<BracketedExpressionParser>();
  }
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken: {
    return std::make_unique<ObjectExpressionParser>();
  }

  default:
    break;
  };

  return std::make_unique<DefaultPrimaryExpressionParser>();
}
