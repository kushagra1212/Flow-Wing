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

#include "ASTBuilder.h"
#include "src/ASTBuilder/parsers/CompilationUnitParser/CompilationUnitParser.h"
#include "src/ASTBuilder/parsers/ParserContext/ParserContext.h"
#include "src/compiler/CompilationContext/CompilationContext.h"
#include "src/syntax/CompilationUnitSyntax.h"

namespace flow_wing {

namespace parser {

ASTBuilder::ASTBuilder(CompilationContext &context)
    : m_parser_ctx(std::make_unique<ParserContext>(context)) {}

ASTBuilder::~ASTBuilder() = default;

std::unique_ptr<syntax::CompilationUnitSyntax> ASTBuilder::create() {
  return std::make_unique<CompilationUnitParser>(m_parser_ctx.get())->parse();
}

} // namespace parser
} // namespace flow_wing