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


#include "FloatTypeConverter.h"

FloatTypeConverter::FloatTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *FloatTypeConverter::convertExplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int64Keyword:
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSIToFP(
        value, llvm::Type::getFloatTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    return _builder->CreateFPTrunc(
        value, llvm::Type::getFloatTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    return _builder->CreateUIToFP(
        value, llvm::Type::getFloatTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    llvm::Value *val = _builder->CreateCall(
        _module->getFunction(INNERS::FUNCTIONS::STRING_TO_DOUBLE), {value});
    return this->convertExplicit(val);
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to double"));

  return nullptr;
}

llvm::Value *FloatTypeConverter::convertImplicit(llvm::Value *&value) {
  llvm::Value *res = nullptr;

  SyntaxKindUtils::SyntaxKind type =
      this->_mapper->mapLLVMTypeToCustomType(value->getType());

  switch (type) {
  case SyntaxKindUtils::SyntaxKind::Int32Keyword:
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    return _builder->CreateSIToFP(
        value, llvm::Type::getDoubleTy(_builder->getContext()));
  }
  case SyntaxKindUtils::SyntaxKind::Int64Keyword: {
    _logger->LogError((

        "Implicit conversion from int64 to deci32 is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    _logger->LogError((

        "Implicit conversion from deci to deci32 is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {
    return value;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    _logger->LogError((

        "Implicit conversion from bool to double is not "
        "supported for variable with predefined type"));
    return nullptr;
  }
  case SyntaxKindUtils::SyntaxKind::StrKeyword: {
    _logger->LogError((

        "Implicit conversion from string to double is not "
        "supported for variable with predefined type"));

    return nullptr;
  }
  default:
    break;
  }

  _logger->LogError(("Unsupported type for conversion to double"));

  return nullptr;
}