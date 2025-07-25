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


#ifndef __FUNCTION_DECLARATION_MANAGER_H__
#define __FUNCTION_DECLARATION_MANAGER_H__

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include "../../constants/FlowWingIRConstants.h"
#include "../../context/CodeGenerationContext.h"

using namespace FLOWWING::IR::CONSTANTS;

class FunctionDeclarationManager {
public:
  FunctionDeclarationManager(CodeGenerationContext *codeGenerationContext);

  void initialize();

private:
  llvm::Module *TheModule;
  llvm::LLVMContext *TheContext;

  llvm::Function *declareFunction(const std::string &functionName,
                                  llvm::FunctionType *functionType);

  llvm::Function *declarePrintFn();
  llvm::Function *declareConcatStringsFn();
  llvm::Function *declareStringLengthFn();
  llvm::Function *declareItosFn();
  llvm::Function *declareDtosFn();
  llvm::Function *declareGetMallocPtrOfStringConstantFn();
  llvm::Function *declareGetMallocPtrofIntConstantFn();
  llvm::Function *declareCompareStringsFn();
  llvm::Function *declareLessThanStringsFn();
  llvm::Function *declareLessThanOrEqualStringsFn();
  llvm::Function *declareGreaterThanStringsFn();
  llvm::Function *declareGreaterThanOrEqualStringsFn();
  llvm::Function *declareEqualStringsFn();
  llvm::Function *declareGetInputFn();
  llvm::Function *declareStringToIntFn();
  llvm::Function *declareStringToLongFn();
  llvm::Function *declareStringToDoubleFn();
  llvm::Function *declarePrintfFn();
  llvm::Function *declarePutChar();

  // GC
  llvm::Function *declareGC_Malloc();

  llvm::Function *declareRaiseExceptionFn();
  llvm::Function *declareMallocFunctionFn();
};

#endif // __FUNCTION_DECLARATION_MANAGER_H__
