/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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



#pragma once

#include "src/SourceTokenizer/TokenKind/TokenKind.h"
namespace flow_wing {
namespace syntax {

struct OperatorPrecedence {
  static int getPrefixPrecedence(lexer::TokenKind kind);
  static int getInfixPrecedence(lexer::TokenKind kind);
  static int getPostfixPrecedence(lexer::TokenKind kind);

  /// RHS of `module::name` must not bind tighter than postfix `(`/`[`/`.` (14).
  /// So `m::T()` is a call on `m::T`, not `m::(T())`.
  static constexpr int kModuleAccessRhsPrecedenceFloor = 15;
};

} // namespace syntax
} // namespace flow_wing
