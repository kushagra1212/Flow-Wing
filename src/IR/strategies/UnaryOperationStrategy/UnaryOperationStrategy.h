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


#ifndef FLOWWING_UNARYOPERATIONSTRATEGY_H
#define FLOWWING_UNARYOPERATIONSTRATEGY_H

#include "../../../SemanticAnalyzer/BoundExpressions/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../../../common/Common.h"
#include "../../LLVMTypeConversion/BoolTypeConverter/BoolTypeConverter.h"
#include "../../LLVMTypeConversion/DoubleTypeConverter/DoubleTypeConverter.h"
#include "../../LLVMTypeConversion/Int32TypeConverter/Int32TypeConverter.h"
#include "../../LLVMTypeConversion/Int8TypeConverter/Int8TypeConverter.h"
#include "../../LLVMTypeConversion/StringTypeConverter/StringTypeConverter.h"
#include "../../LLVMTypeConversion/TypeSpecificValueVisitor.h"
#include "utility.h"
#include "llvm/IR/Value.h"

class UnaryOperationStrategy {
public:
  std::unique_ptr<BoolTypeConverter> _boolTypeConverter;
  std::unique_ptr<DoubleTypeConverter> _doubleTypeConverter;
  std::unique_ptr<Int32TypeConverter> _int32TypeConverter;
  std::unique_ptr<Int8TypeConverter> _int8TypeConverter;
  std::unique_ptr<StringTypeConverter> _stringTypeConverter;
  std::unique_ptr<TypeSpecificValueVisitor> _typeSpecificValueVisitor;

  CodeGenerationContext *_codeGenerationContext;

  llvm::Module *TheModule = nullptr;
  llvm::IRBuilder<> *Builder = nullptr;
  llvm::LLVMContext *TheContext = nullptr;

  UnaryOperationStrategy(CodeGenerationContext *context)
      : _boolTypeConverter(std::make_unique<BoolTypeConverter>(context)),
        _doubleTypeConverter(std::make_unique<DoubleTypeConverter>(context)),
        _int32TypeConverter(std::make_unique<Int32TypeConverter>(context)),
        _int8TypeConverter(std::make_unique<Int8TypeConverter>(context)),
        _stringTypeConverter(std::make_unique<StringTypeConverter>(context)),
        _typeSpecificValueVisitor(std::make_unique<TypeSpecificValueVisitor>()),
        _codeGenerationContext(context), TheModule(context->getModule().get()),
        Builder(context->getBuilder().get()),
        TheContext(context->getContext().get()){};

  virtual llvm::Value *
  performOperation(llvm::Value *val, BoundUnaryExpression *unaryExpression) = 0;

  virtual llvm::Value *
  performOperation(llvm::Value *val,
                   BinderKindUtils::BoundUnaryOperatorKind unaryOperator) = 0;
};

#endif // FLOWWING_BINARYOPERATIONSTRATEGY_H