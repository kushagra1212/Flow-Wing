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
#include "src/IR/LLVMTypeConversion/DoubleTypeConverter/DoubleTypeConverter.h"
#include "src/IR/LLVMTypeConversion/Int32TypeConverter/Int32TypeConverter.h"
#include "src/IR/LLVMTypeConversion/Int8TypeConverter/Int8TypeConverter.h"
#include "src/IR/LLVMTypeConversion/StringTypeConverter/StringTypeConverter.h"
#include "src/IR/LLVMTypeConversion/TypeSpecificValueVisitor.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundBinaryExpression/BoundBinaryExpression.h"
#include "src/common/Common.h"
#include "utility.h"
#include "llvm/IR/Value.h"

class BinaryOperationStrategy {
public:
  std::unique_ptr<BoolTypeConverter> _boolTypeConverter;
  std::unique_ptr<DoubleTypeConverter> _doubleTypeConverter;
  std::unique_ptr<Int32TypeConverter> _int32TypeConverter;
  std::unique_ptr<StringTypeConverter> _stringTypeConverter;
  std::unique_ptr<Int8TypeConverter> _int8TypeConverter;
  std::unique_ptr<FloatTypeConverter> _floatTypeConverter;
  std::unique_ptr<TypeSpecificValueVisitor> _typeSpecificValueVisitor;

  CodeGenerationContext *_codeGenerationContext;

  llvm::Module *TheModule = nullptr;
  llvm::IRBuilder<> *Builder = nullptr;
  llvm::LLVMContext *TheContext = nullptr;

  BinaryOperationStrategy(CodeGenerationContext *context)
      : _boolTypeConverter(std::make_unique<BoolTypeConverter>(context)),
        _doubleTypeConverter(std::make_unique<DoubleTypeConverter>(context)),
        _int32TypeConverter(std::make_unique<Int32TypeConverter>(context)),
        _stringTypeConverter(std::make_unique<StringTypeConverter>(context)),
        _int8TypeConverter(std::make_unique<Int8TypeConverter>(context)),
        _floatTypeConverter(std::make_unique<FloatTypeConverter>(context)),
        _typeSpecificValueVisitor(std::make_unique<TypeSpecificValueVisitor>()),
        _codeGenerationContext(context), TheModule(context->getModule().get()),
        Builder(context->getBuilder().get()),
        TheContext(context->getContext().get()) {};

  virtual llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) = 0;

  virtual llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BinderKindUtils::BoundBinaryOperatorKind binaryOp) = 0;

  virtual ~BinaryOperationStrategy() = default;
};
