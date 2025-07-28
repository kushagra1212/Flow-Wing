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

#include "GlobalTypeInitializer.h"

GlobalTypeInitializer::GlobalTypeInitializer(
    CodeGenerationContext *codeGenerationContext)
    : TheModule(codeGenerationContext->getModule().get()),
      TheContext(codeGenerationContext->getContext().get()) {}

void GlobalTypeInitializer::initialize() { this->initializeDynamicValueType(); }

void GlobalTypeInitializer::initializeDynamicValueType() {

  llvm::StructType *existingType = llvm::StructType::getTypeByName(
      *TheContext, DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

  if (existingType) {
    return;
  }

  llvm::Type *tagType = llvm::IntegerType::get(*TheContext, 32);   // i32
  llvm::Type *valueType = llvm::IntegerType::get(*TheContext, 64); // i64

  llvm::StructType *dynamicValueType = llvm::StructType::create(
      *TheContext, DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

  dynamicValueType->setBody({tagType, valueType});
}
