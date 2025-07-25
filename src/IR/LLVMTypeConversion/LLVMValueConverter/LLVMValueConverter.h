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


#ifndef __FLOWWING_LLVM_VALUE_CONVERTER_H__
#define __FLOWWING_LLVM_VALUE_CONVERTER_H__

#include "../../../syntax/SyntaxKindUtils.h"
#include "../../context/CodeGenerationContext.h"
#include "../../logger/LLVMLogger.h"
#include "../../mappers/TypeMapper/TypeMapper.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

class LLVMValueConverter {
public:
  LLVMValueConverter(CodeGenerationContext *context);

  llvm::Value *convertToLLVMValue(std::any value,
                                  SyntaxKindUtils::SyntaxKind kind);
  llvm::Value *convertToTypedLLVMValue(std::any value,
                                       SyntaxKindUtils::SyntaxKind kind,
                                       SyntaxKindUtils::SyntaxKind type);

  llvm::Value *stringToTypedLLVMValue(std::string value,
                                      SyntaxKindUtils::SyntaxKind kind,
                                      SyntaxKindUtils::SyntaxKind type);

  llvm::Value *int32ToLLVMValue(int value);
  llvm::Value *doubleToLLVMValue(double value);
  llvm::Value *boolToLLVMValue(bool value);
  llvm::Value *stringToLLVMValue(std::string value,
                                 SyntaxKindUtils::SyntaxKind kind);

private:
  llvm::IRBuilder<> *_builder;
  llvm::Module *_module;
  TypeMapper *_mapper;
  LLVMLogger *_logger;
  llvm::LLVMContext *_llvmContext;
  CodeGenerationContext *_codeGenerationContext;
};

#endif // __FLOWWING_LLVM_VALUE_CONVERTER_H__