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
#include "src/IR/LLVMTypeConversion/BoolTypeConverter/BoolTypeConverter.h"
#include "src/IR/LLVMTypeConversion/ExplicitConverter.h"
#include "src/IR/strategies/BinaryOperationStrategy/Int32BinaryOperationStrategy/Int32BinaryOperationStrategy.h"
#include "src/IR/context/CodeGenerationContext.h"
#include "ValueCaster/ValueCaster.h"

namespace DYNAMIC_VALUE_HANDLER {

llvm::Value *assignRHSValueToLHSDynamicValue(llvm::Value *lhsPtr,
                                             const std::string &variableName,
                                             llvm::Value *rhsValue,
                                             CodeGenerationContext *context,
                                             llvm::IRBuilder<> *&Builder);

llvm::Value *
generateDynamicDispatch(llvm::Value *dynamicValue,
                        CodeGenerationContext *context,
                        llvm::IRBuilder<> *&Builder,
                        const std::function<void(llvm::Value *)> &handler);

void assignRHSDynamicValueToLHSDynamicValue(llvm::Value *lhsDynamicValue,
                                            llvm::Value *rhsDynamicValue,
                                            CodeGenerationContext *context,
                                            llvm::IRBuilder<> *&Builder);

std::pair<llvm::Value *, llvm::Value *>
getDynamicStoredValueAndType(llvm::Value *&dynamicValue,
                             CodeGenerationContext *&context,
                             llvm::IRBuilder<> *&Builder);

void assignRHSDynamicValueToLHSVariable(llvm::Value *lhsVariable,
                                        llvm::Type *lhsType,
                                        llvm::Value *rhsDynamicValue,
                                        CodeGenerationContext *context,
                                        llvm::IRBuilder<> *&Builder);

} // namespace DYNAMIC_VALUE_HANDLER
