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


// StructTypeBuilder.h
#ifndef __FLOWWING_STRUCT_TYPE_BUILDER_H__
#define __FLOWWING_STRUCT_TYPE_BUILDER_H__

#include "src/common/constants/FlowWingUtilsConstants.h"
#include "src/IR/TypeBuilder/ReferenceTypeBuilder/ReferenceTypeBuilder.h"
#include "src/IR/TypeBuilder/TypeBuilderInterface.h"

class StructTypeBuilder : public TypeBuilderInterface {
public:
  StructTypeBuilder(CodeGenerationContext *context);
  void buildType() override;
  llvm::StructType *get() const override;
  const std::vector<llvm::Type *> &getMemberTypes() const;

  const uint64_t getMemberTypeofDynVar(llvm::Type *type) const;

  const bool isDyn(llvm::Type *type) const;

  const bool isGlobalVar(const std::string &varName) const;

  llvm::Value *getMemberValueOfDynVar(llvm::Value *v,
                                      const std::string &varName) const;

  llvm::Value *setMemberValueOfDynVar(llvm::Value *v, llvm::Value *value,
                                      llvm::Type *variableType,
                                      const std::string &variableName) const;

private:
  llvm::StructType *_dynamicType;
  std::vector<llvm::Type *> _memberTypesForDynamicTypes;
  llvm::LLVMContext *_context;
};

#endif // __FLOWWING_STRUCT_TYPE_BUILDER_H__
