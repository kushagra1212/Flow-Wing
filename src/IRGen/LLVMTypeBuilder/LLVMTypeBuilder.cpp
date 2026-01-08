/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
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

#include "src/IRGen/LLVMTypeBuilder/LLVMTypeBuilder.hpp"
#include "src/IRGen/FlowWingConstants/FlowWingConstants.hpp"
#include "src/SemanticAnalyzer/Builtins/Builtins.hpp"
#include "src/common/types/CustomObjectType/CustomObjectType.hpp"
#include "src/common/types/FunctionType/FunctionType.hpp"
#include "src/utils/LogConfig.h"
#include "llvm/IR/DerivedTypes.h"

namespace flow_wing {
namespace ir_gen {

llvm::Type *LLVMTypeBuilder::getLLVMType(const types::Type *type) {
  if (!type)
    return llvm::Type::getVoidTy(m_context);

  if (m_type_cache.find(type) != m_type_cache.end()) {
    return m_type_cache[type];
  }

  llvm::Type *llvmType = nullptr;

  switch (type->getKind()) {
  case types::TypeKind::kPrimitive:
    llvmType = convertPrimitive(type);
    break;
  case types::TypeKind::kFunction:
    llvmType = convertFunction(static_cast<const types::FunctionType *>(type));
    break;
  case types::TypeKind::kArray:
    llvmType = convertArray(static_cast<const types::ArrayType *>(type));
    break;
  case types::TypeKind::kClass:
    llvmType = convertClass(static_cast<const types::ClassType *>(type));
    break;
  case types::TypeKind::kObject: {
    llvmType =
        convertObject(static_cast<const types::CustomObjectType *>(type));
    break;
  }
  default:
    assert(false && "Unsupported type conversion");
    return nullptr;
  }

  m_type_cache[type] = llvmType;
  return llvmType;
}

llvm::Type *LLVMTypeBuilder::convertPrimitive(const types::Type *type) {
  if (type == analysis::Builtins::m_int32_type_instance.get())
    return llvm::Type::getInt32Ty(m_context);
  if (type == analysis::Builtins::m_int64_type_instance.get())
    return llvm::Type::getInt64Ty(m_context);
  if (type == analysis::Builtins::m_int8_type_instance.get())
    return llvm::Type::getInt8Ty(m_context);
  if (type == analysis::Builtins::m_deci_type_instance.get())
    return llvm::Type::getDoubleTy(m_context);
  if (type == analysis::Builtins::m_deci32_type_instance.get())
    return llvm::Type::getFloatTy(m_context);
  if (type == analysis::Builtins::m_bool_type_instance.get())
    return llvm::Type::getInt1Ty(m_context);
  if (type == analysis::Builtins::m_str_type_instance.get())
    return llvm::Type::getInt8PtrTy(m_context);
  if (type == analysis::Builtins::m_nthg_type_instance.get())
    return llvm::Type::getVoidTy(m_context);
  if (type == analysis::Builtins::m_char_type_instance.get())
    return llvm::Type::getInt32Ty(m_context);
  if (type == analysis::Builtins::m_dynamic_type_instance.get())
    return createDynamicValueType();
  if (type == analysis::Builtins::m_nirast_type_instance.get())
    return llvm::Type::getInt8PtrTy(m_context);

  assert(false && "Unsupported primitive type");
  return nullptr;
}

llvm::Type *
LLVMTypeBuilder::convertObject(const types::CustomObjectType *type) {

  if (m_type_cache.find(type) != m_type_cache.end()) {
    return m_type_cache[type];
  }

  llvm::StructType *object_type =
      llvm::StructType::create(m_context, type->getCustomTypeName());

  m_type_cache[type] = object_type;
  CODEGEN_DEBUG_LOG("Building Object Type", type->getName(),
                    object_type->getStructName().str());
  std::vector<llvm::Type *> elements;

  assert(type && "Object type has no fields");

  for (const auto &[field_name, field_type] : type->getFieldTypesMap()) {
    auto field_llvm_type = getLLVMType(field_type.get());
    assert(field_llvm_type && "Field LLVM type is null");
    if (field_type->getKind() == types::TypeKind::kObject) {
      elements.push_back(field_llvm_type->getPointerTo());
    } else {
      elements.push_back(field_llvm_type);
    }
  }

  object_type->setBody(elements);
  return object_type;
}

llvm::Type *LLVMTypeBuilder::createDynamicValueType() {

  auto dynamic_type = llvm::StructType::getTypeByName(
      m_context, constants::types::kDynamic_type_name);

  if (dynamic_type) {
    return dynamic_type;
  }

  llvm::Type *tag_type = llvm::IntegerType::get(m_context, 32);   // i32
  llvm::Type *value_type = llvm::IntegerType::get(m_context, 64); // i64

  dynamic_type =
      llvm::StructType::create(m_context, constants::types::kDynamic_type_name);

  dynamic_type->setBody({tag_type, value_type});
  return dynamic_type;
}

llvm::Type *LLVMTypeBuilder::convertFunctionParameter(
    const types::ParameterType *param_type) {
  if (param_type->type_convention == types::TypeConvention::kFlowWing) {
    return llvm::Type::getInt8PtrTy(m_context);
  }

  if (param_type->type == analysis::Builtins::m_dynamic_type_instance) {
    return createDynamicValueType()->getPointerTo();
  }

  return getLLVMType(param_type->type.get());
}

llvm::Type *LLVMTypeBuilder::convertFunctionReturnType(
    const types::ReturnType *return_type) {
  if (return_type->type_convention == types::TypeConvention::kFlowWing) {
    return llvm::Type::getInt8PtrTy(m_context);
  }

  return getLLVMType(return_type->type.get());
}

llvm::FunctionType *
LLVMTypeBuilder::convertFunction(const types::FunctionType *funcType) {

  llvm::Type *result_type =
      convertFunctionReturnType(funcType->getReturnTypes()[0].get());

  std::vector<llvm::Type *> args;
  for (const auto &param : funcType->getParameterTypes()) {
    args.push_back(convertFunctionParameter(param.get()));
  }

  return llvm::FunctionType::get(result_type, args, funcType->isVariadic());
}

llvm::Type *LLVMTypeBuilder::convertArray(const types::ArrayType *arrType) {
  llvm::Type *underlying_type = getLLVMType(arrType->getUnderlyingType().get());
  llvm::Type *array_type = underlying_type;
  for (const auto &dimension : arrType->getDimensions()) {
    array_type = llvm::ArrayType::get(array_type, dimension);
  }
  return array_type;
}

llvm::Type *LLVMTypeBuilder::convertClass(
    [[maybe_unused]] const types::ClassType *classType) {

  // Todo(kushagra): Implement this
  assert(false && "Class type conversion not implemented");
  return nullptr;
}
} // namespace ir_gen

} // namespace flow_wing