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

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

#include "src/IR/context/CodeGenerationContext.h"

class GlobalTypeInitializer {
public:
  GlobalTypeInitializer(CodeGenerationContext *codeGenerationContext);

  void initialize();

private:
  llvm::Module *TheModule;
  llvm::LLVMContext *TheContext;

  void initializeDynamicValueType();
};
