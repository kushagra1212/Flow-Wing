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

// StructTypeBuilder.cpp
#include "StructTypeBuilder.h"

#include "src/IR/context/CodeGenerationContext.h"

StructTypeBuilder::StructTypeBuilder(
    CodeGenerationContext *_codeGenerationContext)
    : TypeBuilderInterface(_codeGenerationContext) {
  _context = _codeGenerationContext->getContext().get();
  _memberTypesForDynamicTypes = {
      llvm::Type::getInt32Ty(*_context), llvm::Type::getDoubleTy(*_context),
      llvm::Type::getInt1Ty(*_context),  llvm::Type::getInt8PtrTy(*_context),
      llvm::Type::getInt8Ty(*_context),  llvm::Type::getInt64Ty(*_context),
      llvm::Type::getFloatTy(*_context),
  };
}

void StructTypeBuilder::buildType() {
  this->_dynamicType = llvm::StructType::create(*_context, "DynamicType");
  this->_dynamicType->setBody(_memberTypesForDynamicTypes);
}

llvm::StructType *StructTypeBuilder::get() const { return _dynamicType; }

const std::vector<llvm::Type *> &StructTypeBuilder::getMemberTypes() const {
  return _memberTypesForDynamicTypes;
}

uint64_t StructTypeBuilder::getMemberTypeofDynVar(llvm::Type *type) const {
  uint64_t index = std::numeric_limits<size_t>::max();
  for (uint64_t i = 0; i < this->_memberTypesForDynamicTypes.size(); i++) {
    if (this->_memberTypesForDynamicTypes[i] == type) {
      index = i;
      break;
    }
  }

  if (index == std::numeric_limits<size_t>::max()) {
    std::string typeUsedByUser =
        _codeGenerationContext->getMapper()->getLLVMTypeName(type);

    _codeGenerationContext->getLogger()->LogError(
        "Unsupported type for dynamic type: " + typeUsedByUser);

    index = 0;
  }

  return index;
}

bool StructTypeBuilder::isDyn(llvm::Type *type) const {
  return type == this->_dynamicType;
}

llvm::Value *StructTypeBuilder::getMemberValueOfDynVar(
    llvm::Value *v, const std::string &variableName) const {

  uint64_t index;

  if (isGlobalVar(variableName)) {
    index = _codeGenerationContext->getAllocaChain()->getGlobalTypeIndex(
        variableName);
  } else {
    index =
        _codeGenerationContext->getAllocaChain()->getTypeIndex(variableName);
  }

  llvm::Value *elementPtr =
      _codeGenerationContext->getBuilder()->CreateStructGEP(
          this->_dynamicType, v, static_cast<uint32_t>(index));

  _codeGenerationContext->getValueStackHandler()->push(
      "", elementPtr, "dynamic", this->getMemberTypes()[index], v);

  return _codeGenerationContext->getBuilder()->CreateLoad(
      this->getMemberTypes()[index], elementPtr);
}

llvm::Value *StructTypeBuilder::setMemberValueOfDynVar(
    llvm::Value *v, llvm::Value *value, llvm::Type *variableType,
    const std::string &variableName) const {

  uint64_t index = this->getMemberTypeofDynVar(variableType);

  if (isGlobalVar(variableName)) {
    _codeGenerationContext->getAllocaChain()->setGlobalTypeIndex(variableName,
                                                                 index);
  } else {
    _codeGenerationContext->getAllocaChain()->setTypeIndex(variableName, index);
  }

  llvm::Value *elementPtr =
      _codeGenerationContext->getBuilder()->CreateStructGEP(
          this->_dynamicType, v, static_cast<uint32_t>(index));

  return _codeGenerationContext->getBuilder()->CreateStore(value, elementPtr);
}

bool StructTypeBuilder::isGlobalVar(const std::string &varName) const {
  return varName.find(FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX) == 0;
}