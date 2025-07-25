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

#include "../../syntax/statements/FunctionDeclarationSyntax/FunctionDeclarationSyntax.h"
#include "../../syntax/statements/GlobalStatementSyntax/GlobalStatementSyntax.h"
#include "BoundGlobalScope/BoundGlobalScope.h"
#include "BoundScope/BoundScope.h"
#include "MemberBinder/MemberBinder.h"
#include "SyntaxBinderContext/SyntaxBinderContext.h"
#include <memory>

class SyntaxBinder {
  std::unique_ptr<SyntaxBinderContext> _context = nullptr;

public:
  SyntaxBinder(std::unique_ptr<BoundScope> scope,
               FlowWing::DiagnosticHandler *diagnosticHandler);

  std::unique_ptr<BoundStatement> bind(CompilationUnitSyntax *syntax);

  std::unique_ptr<SyntaxBinderContext> &getContextRef();
};
