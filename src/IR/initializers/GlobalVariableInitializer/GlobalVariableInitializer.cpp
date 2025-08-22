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

#include "GlobalVariableInitializer.h"

GlobalVariableInitializer::GlobalVariableInitializer(
    CodeGenerationContext *codeGenerationContext)
    : TheModule(codeGenerationContext->getModule().get()),
      TheContext(codeGenerationContext->getContext().get()),
      _codeGenerationContext(codeGenerationContext) {

  i8Type = llvm::Type::getInt8Ty(*TheContext);
  i32Type = llvm::Type::getInt32Ty(*TheContext);
}

void GlobalVariableInitializer::initialize() {
  this->initializeTrue();
  this->initializeFalse();
  this->initializeI8Null();
  this->initializeBreakCount();
  this->initializeContinueCount();
  this->initializeErrorCount();
  this->initializeDynamicValueTypes();
}

void GlobalVariableInitializer::initializeTrue() {
  new llvm::GlobalVariable(
      *TheModule, llvm::ArrayType::get(i8Type, 5),
      true, // isConstant
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantDataArray::getString(*TheContext, "true\00"),
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE));
}
void GlobalVariableInitializer::initializeFalse() {
  new llvm::GlobalVariable(
      *TheModule, llvm::ArrayType::get(i8Type, 6), true,
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantDataArray::getString(*TheContext, "false\00"),
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE));
}

void GlobalVariableInitializer::initializeI8Null() {
  new llvm::GlobalVariable(
      *TheModule, i8Type, false, llvm::GlobalValue::ExternalLinkage,
      nullptr, // For null, you can pass nullptr as the initializer
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_NULL));
}
void GlobalVariableInitializer::initializeBreakCount() {
  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));
}
void GlobalVariableInitializer::initializeContinueCount() {

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT));
}
void GlobalVariableInitializer::initializeErrorCount() {

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_ERROR_COUNT));
}

void GlobalVariableInitializer::initializeDynamicValueTypes() {

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::InternalLinkage,
      llvm::ConstantInt::get(i32Type, DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT32),
      (DYNAMIC_VALUE::TYPE::TYPE_INT32));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::InternalLinkage,
      llvm::ConstantInt::get(i32Type, DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT64),
      (DYNAMIC_VALUE::TYPE::TYPE_INT64));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::InternalLinkage,
      llvm::ConstantInt::get(i32Type, DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT32),
      (DYNAMIC_VALUE::TYPE::TYPE_FLOAT32));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::InternalLinkage,
      llvm::ConstantInt::get(i32Type, DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT64),
      (DYNAMIC_VALUE::TYPE::TYPE_FLOAT64));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::InternalLinkage,
      llvm::ConstantInt::get(i32Type, DYNAMIC_VALUE::TYPE::VALUE_TYPE::STRING),
      (DYNAMIC_VALUE::TYPE::TYPE_STRING));

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::InternalLinkage,
      llvm::ConstantInt::get(i32Type, DYNAMIC_VALUE::TYPE::VALUE_TYPE::BOOLEAN),
      (DYNAMIC_VALUE::TYPE::TYPE_BOOLEAN));
}