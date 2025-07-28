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

// ReferenceTypeBuilder.h
#pragma once

#include "src/IR/TypeBuilder/TypeBuilderInterface.h"

class TypeBuilderInterface;

class ReferenceTypeBuilder : public TypeBuilderInterface {
public:
  ReferenceTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;

  llvm::Type *getReferencedType() const;

  bool isRef(llvm::Type *type) const;

  llvm::Value *getReferencedValue(llvm::Value *refValue) const;

  const std::vector<llvm::Type *> &getMemberTypes() const;

private:
  llvm::StructType *_referenceType;
  std::vector<llvm::Type *> _memberTypes;
};
