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

#include "src/IR/irGen/Types/LLVMType/LLVMType.h"

// clang-format off
#include "src/diagnostics/Diagnostic/diagnostic_push.h"
#include <llvm/IR/DerivedTypes.h>
#include "src/diagnostics/Diagnostic/diagnostic_pop.h"
// clang-format on

class LLVMFunctionType : public LLVMType {
public:
  LLVMFunctionType(llvm::Type *type, llvm::FunctionType *fType);

  virtual ~LLVMFunctionType() = default;

  virtual inline bool isPointerToFunction() const override { return true; }

  inline llvm::FunctionType *getFunctionType() const { return _fType; }

  virtual inline llvm::Type *getLLVMType() const override { return _fType; }

private:
  llvm::FunctionType *_fType;
};
