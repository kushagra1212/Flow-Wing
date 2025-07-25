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


#include "StatementBinderFactory.h"

#include "BlockStatementBinder/BlockStatementBinder.h"
#include "BreakStatementBinder/BreakStatementBinder.h"
#include "BringStatementBinder/BringStatementBinder.h"
#include "ClassStatementBinder/ClassStatementBinder.h"
#include "ContinueStatementBinder/ContinueStatementBinder.h"
#include "CustomTypeStatementBinder/CustomTypeStatementBinder.h"
#include "ExpressionStatementBinder/ExpressionStatementBinder.h"
#include "ForStatementBinder/ForStatementBinder.h"
#include "IfStatementBinder/IfStatementBinder.h"
#include "ModuleStatementBinder/ModuleStatementBinder.h"
#include "MultipleVariableDeclarationBinder/MultipleVariableDeclarationBinder.h"
#include "OrIfStatementBinder/OrIfStatementBinder.h"
#include "ReturnStatementBinder/ReturnStatementBinder.h"
#include "SwitchStatementBinder/SwitchStatementBinder.h"
#include "VariableDeclarationBinder/VariableDeclarationBinder.h"
#include "WhileStatementBinder/WhileStatementBinder.h"

std::unique_ptr<StatementBinder>
StatementBinderFactory::create(const SyntaxKindUtils::SyntaxKind &kind) {
  switch (kind) {

  case SyntaxKindUtils::SyntaxKind::ExpressionStatement: {
    return std::make_unique<ExpressionStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::VariableDeclaration: {
    return std::make_unique<VariableDeclarationBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::MultipleVariableDeclaration: {
    return std::make_unique<MultipleVariableDeclarationBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::IfStatement: {
    return std::make_unique<IfStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::OrIfStatement: {
    return std::make_unique<OrIfStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::WhileStatement: {
    return std::make_unique<WhileStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ForStatement: {
    return std::make_unique<ForStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::BlockStatement: {
    return std::make_unique<BlockStatementBinder>();
  }

  case SyntaxKindUtils::SyntaxKind::BreakStatement: {
    return std::make_unique<BreakStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ContinueStatement: {
    return std::make_unique<ContinueStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ReturnStatement: {
    return std::make_unique<ReturnStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::BringStatementSyntax: {
    return std::make_unique<BringStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ClassStatement: {
    return std::make_unique<ClassStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::ModuleStatement: {
    return std::make_unique<ModuleStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::CustomTypeStatement: {
    return std::make_unique<CustomTypeStatementBinder>();
  }
  case SyntaxKindUtils::SyntaxKind::SwitchStatementSyntax: {
    return std::make_unique<SwitchStatementBinder>();
  }

  default:
    break;
  }

  assert("Unexpected syntax kind for statement binder" && false);

  return nullptr;
}