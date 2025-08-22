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
#include "BreakStatementParser/BreakStatementParser.h"
#include "BringStatementParser/BringStatementParser.h"
#include "ClassStatementParser/ClassStatementParser.h"
#include "ContinueStatementParser/ContinueStatementParser.h"
#include "CustomTypeStatementParser/CustomTypeStatementParser.h"
#include "ExpressionStatementParser/ExpressionStatementParser.h"
#include "ForStatementParser/ForStatementParser.h"
#include "IfStatementParser/IfStatementParser.h"
#include "ModuleStatementParser/ModuleStatementParser.h"
#include "ReturnStatementParser/ReturnStatementParser.h"
#include "SwitchStatementParser/SwitchStatementParser.h"
#include "VariableDeclarationParser/VariableDeclarationParser.h"
#include "WhileStatementParser/WhileStatementParser.h"

std::unique_ptr<StatementParser> StatementParserFactory::createStatementParser(
    const SyntaxKindUtils::SyntaxKind &kind) {
  switch (kind) {
  case SyntaxKindUtils::SyntaxKind::OpenBraceToken:
    return std::make_unique<BlockStatementParser>();
  case SyntaxKindUtils::SyntaxKind::VarKeyword:
  case SyntaxKindUtils::SyntaxKind::ConstKeyword:
    return std::make_unique<VariableDeclarationParser>();
  case SyntaxKindUtils::SyntaxKind::IfKeyword:
    return std::make_unique<IfStatementParser>();
  case SyntaxKindUtils::SyntaxKind::WhileKeyword:
    return std::make_unique<WhileStatementParser>();
  case SyntaxKindUtils::SyntaxKind::ForKeyword:
    return std::make_unique<ForStatementParser>();
  case SyntaxKindUtils::SyntaxKind::BreakKeyword:
    return std::make_unique<BreakStatementParser>();
  case SyntaxKindUtils::SyntaxKind::ContinueKeyword:
    return std::make_unique<ContinueStatementParser>();
  case SyntaxKindUtils::SyntaxKind::ReturnKeyword:
    return std::make_unique<ReturnStatementParser>();
  case SyntaxKindUtils::SyntaxKind::BringKeyword:
    return std::make_unique<BringStatementParser>();
  case SyntaxKindUtils::SyntaxKind::TypeKeyword:
    return std::make_unique<CustomTypeStatementParser>();
  case SyntaxKindUtils::SyntaxKind::ClassKeyword:
    return std::make_unique<ClassStatementParser>();
  case SyntaxKindUtils::SyntaxKind::ModuleKeyword:
    return std::make_unique<ModuleStatementParser>();
  case SyntaxKindUtils::SyntaxKind::SwitchKeyword:
    return std::make_unique<SwitchStatementParser>();
  default:
    return std::make_unique<ExpressionStatementParser>();
  }
}