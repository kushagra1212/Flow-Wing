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


#include "GStringTypeConverter.h"

GStringTypeConverter::GStringTypeConverter(CodeGenerationContext *context)
    : TypeConverterBase(context){};

llvm::Value *
GStringTypeConverter::convertExplicit(llvm::Value *&possibleGlobalVariable) {
  return convertImplicit(possibleGlobalVariable);
}

llvm::Value *
GStringTypeConverter::convertImplicit(llvm::Value *&possibleGlobalVariable) {

  llvm::Value *res = nullptr;
  auto globalVar = llvm::dyn_cast<llvm::GlobalVariable>(possibleGlobalVariable);

  if (!globalVar) {
    _logger->LogError((

        "Unsupported type for conversion to String (not a global variable)"));
    return res;
  }

  std::unique_ptr<StringTypeConverter> stringConverter =
      std::make_unique<StringTypeConverter>(this->_codeGenerationContext);
  if (globalVar->getValueType()->isIntegerTy(32)) {
    llvm::Value *val = _builder->CreateLoad(
        llvm::Type::getInt32Ty(_builder->getContext()), globalVar);

    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::ITOS),
                                {val});
  } else if (globalVar->getValueType()->isIntegerTy(1)) {
    llvm::Value *val = _builder->CreateLoad(
        llvm::Type::getInt1Ty(_builder->getContext()), globalVar);

    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::ITOS),
                                {val});
  } else if (globalVar->getValueType()->isDoubleTy()) {
    llvm::Value *val = _builder->CreateLoad(
        llvm::Type::getDoubleTy(_builder->getContext()), globalVar);

    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::DTOS),
                                {val});
  } else if (globalVar->getValueType()->isPointerTy()) {
    llvm::Value *val = _builder->CreateLoad(
        llvm::Type::getInt8PtrTy(_builder->getContext()), globalVar);

    // bitcast to i8*

    return val;
  } else if (globalVar->getValueType()->isIntegerTy(8)) {
    llvm::Value *val = _builder->CreateLoad(
        llvm::Type::getInt8Ty(_builder->getContext()), globalVar);

    // bitcast to i8*

    return val;
  } else if (globalVar->getValueType()->isIntegerTy(64)) {
    llvm::Value *val = _builder->CreateLoad(
        llvm::Type::getInt64Ty(_builder->getContext()), globalVar);

    return _builder->CreateCall(_module->getFunction(INNERS::FUNCTIONS::DTOS),
                                {val});
  }

  // _logger->LogError((
  //
  //     "Unsupported type for conversion to String (not a global variable)"));

  return nullptr;
}