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


// ContainerTypeBuilder.cpp
#include "ContainerTypeBuilder.h"

#include "src/IR/context/CodeGenerationContext.h"

ContainerTypeBuilder::ContainerTypeBuilder(
    CodeGenerationContext *_codeGenerationContext)
    : TypeBuilderInterface(_codeGenerationContext) {

  _body = {
      llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getDoubleTy(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt1Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt8PtrTy(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt8Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getInt64Ty(*_codeGenerationContext->getContext().get()),
      llvm::Type::getFloatTy(*_codeGenerationContext->getContext().get()),
  };
}

void ContainerTypeBuilder::buildType() {
  this->_dynamicType = llvm::StructType::create(
      *_codeGenerationContext->getContext().get(), "DynamicTypeContainer");
  this->_dynamicType->setBody(_body);
}

llvm::StructType *ContainerTypeBuilder::get() const { return _dynamicType; }

const std::vector<llvm::Type *> &ContainerTypeBuilder::getMemberTypes() const {
  return _body;
}

const uint64_t
ContainerTypeBuilder::getIndexofMemberType(llvm::Type *type) const {
  int index = -1;
  for (uint64_t i = 0; i < this->_body.size(); i++) {
    if (this->_body[i] == type) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    std::string typeUsedByUser =
        _codeGenerationContext->getMapper()->getLLVMTypeName(type);

    _codeGenerationContext->getLogger()->LogError(
        "Unsupported type for dynamic type: " + typeUsedByUser);

    index = 0;
  }

  return index;
}
