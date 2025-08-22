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

#include "ReferenceTypeBuilder.h"

#include "src/IR/context/CodeGenerationContext.h"

ReferenceTypeBuilder::ReferenceTypeBuilder(CodeGenerationContext *context)
    : TypeBuilderInterface(context) {
  _memberTypes = {
      llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get()),
  };
}

void ReferenceTypeBuilder::buildType() {
  this->_referenceType = llvm::StructType::create(
      *_codeGenerationContext->getContext().get(), "referenceType");

  this->_referenceType->setBody(_memberTypes);
}

llvm::StructType *ReferenceTypeBuilder::get() const { return _referenceType; }

llvm::Type *ReferenceTypeBuilder::getReferencedType() const {
  return llvm::Type::getInt32Ty(*_codeGenerationContext->getContext().get());
}

bool ReferenceTypeBuilder::isRef(llvm::Type *type) const {
  return type == this->_referenceType;
}

llvm::Value *
ReferenceTypeBuilder::getReferencedValue(llvm::Value *refValue) const {
  return _codeGenerationContext->getBuilder()->CreateStructGEP(
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          SyntaxKindUtils::SyntaxKind::Int32Keyword),
      refValue, 0);
}

const std::vector<llvm::Type *> &ReferenceTypeBuilder::getMemberTypes() const {
  return _memberTypes;
}
