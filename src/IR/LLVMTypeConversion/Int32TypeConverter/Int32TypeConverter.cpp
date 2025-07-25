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


#include "Int32TypeConverter.h"

Int32TypeConverter::Int32TypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *Int32TypeConverter::convertExplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  llvm::LLVMContext *TheContext = _codeGenerationContext->getContext().get();

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSExt(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    return _builder->CreateTrunc(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword:
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return _builder->CreateFPToSI(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return _builder->CreateZExt(value, llvm::Type::getInt32Ty(*TheContext));
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    // TODO: Implement explicit conversion from string to int

    return _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_INT), {value});
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to int32"));

  return res;
}

llvm::Value *Int32TypeConverter::convertImplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSExt(value,
                                llvm::Type::getInt32Ty(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    this->_logger->LogError(("Implicit conversion from int64 to int32 "
                             "is not supported for variable with "
                             "predefined type"));
    return nullptr;
  }

  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    this->_logger->LogError(("Implicit conversion from deci to int32 "
                             "is not supported for variable with "
                             "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    this->_logger->LogError(("Implicit conversion from deci32 to int32 "
                             "is not supported for variable with "
                             "predefined type"));

    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    this->_logger->LogError(("Implicit conversion from bool to int32"));

    return _builder->CreateZExt(value,
                                llvm::Type::getInt32Ty(_builder->getContext()));
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    this->_logger->LogError(("Implicit conversion from string to int32 is "
                             "not supported for variable with predefined "
                             "type"));

    return nullptr;
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to int32"));

  return res;
}