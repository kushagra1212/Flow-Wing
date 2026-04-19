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

#pragma once

#include "src/syntax/CompilationUnitSyntax.h"
#include <memory>

namespace flow_wing {

namespace diagnostic {
class DiagnosticHandler;
} // namespace diagnostic

class CompilationContext;

namespace parser {

class ParserContext;
class ASTBuilder {

public:
  ASTBuilder(CompilationContext &context);

  ~ASTBuilder();

  std::unique_ptr<syntax::CompilationUnitSyntax> create();

private:
  std::unique_ptr<ParserContext> m_parser_ctx = nullptr;
};
} // namespace parser
} // namespace flow_wing
