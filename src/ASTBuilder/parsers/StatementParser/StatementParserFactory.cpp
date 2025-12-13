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

#include "StatementParserFactory.h"

#include "BlockStatementParser/BlockStatementParser.h"
#include "VariableDeclarationParser/VariableDeclarationParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/ASTBuilder/parsers/StatementParser/BreakStatementParser/BreakStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/BringStatementParser/BringStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ClassStatementParser/ClassStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ContinueStatementParser/ContinueStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/CustomTypeStatementParser/CustomTypeStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ExpressionStatementParser/ExpressionStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ForStatementParser/ForStatementParser.h"

#include "src/ASTBuilder/parsers/StatementParser/FunctionStatementParser/FunctionStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/IfStatementParser/IfStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ModuleStatementParser/ModuleStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/ReturnStatementParser/ReturnStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/StatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/SwitchStatementParser/SwitchStatementParser.h"
#include "src/ASTBuilder/parsers/StatementParser/WhileStatementParser/WhileStatementParser.h"
#include "src/SourceTokenizer/TokenKind/TokenKind.h"
#include "src/syntax/NodeKind/NodeKind.h"
#include "src/utils/LogConfig.h"
#include <cassert>

namespace flow_wing {

namespace parser {

std::unique_ptr<StatementParser>
StatementParserFactory::create(ParserContext &context) {

  switch (context.getCurrentTokenKind()) {
  case lexer::TokenKind::kOpenBraceToken:
    return std::make_unique<BlockStatementParser>(&context);
  case lexer::TokenKind::kVarKeyword:
  case lexer::TokenKind::kConstKeyword:
    return std::make_unique<VariableDeclarationParser>(&context);
  case lexer::TokenKind::kIfKeyword:
    return std::make_unique<IfStatementParser>(&context);
  case lexer::TokenKind::kWhileKeyword:
    return std::make_unique<WhileStatementParser>(&context);
  case lexer::TokenKind::kForKeyword:
    return std::make_unique<ForStatementParser>(&context);
  case lexer::TokenKind::kBreakKeyword:
    return std::make_unique<BreakStatementParser>(&context);
  case lexer::TokenKind::kContinueKeyword:
    return std::make_unique<ContinueStatementParser>(&context);
  case lexer::TokenKind::kReturnKeyword:
    return std::make_unique<ReturnStatementParser>(&context);
  case lexer::TokenKind::kBringKeyword:
    return std::make_unique<BringStatementParser>(&context);
  case lexer::TokenKind::kTypeKeyword:
    return std::make_unique<CustomTypeStatementParser>(&context);
  case lexer::TokenKind::kClassKeyword:
    return std::make_unique<ClassStatementParser>(&context);
  case lexer::TokenKind::kModuleKeyword:
    return std::make_unique<ModuleStatementParser>(&context);
  case lexer::TokenKind::kSwitchKeyword:
    return std::make_unique<SwitchStatementParser>(&context);
  case lexer::TokenKind::kFunctionKeyword:
    return std::make_unique<FunctionStatementParser>(&context);
  default:
    return std::make_unique<ExpressionStatementParser>(&context);
  }
}

} // namespace parser

} // namespace flow_wing