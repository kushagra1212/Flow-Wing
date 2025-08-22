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

#include "DynamicValueHandler.h"
#include "ValueCaster/ValueCaster.h"
namespace DYNAMIC_VALUE_HANDLER {

llvm::Value *assignRHSValueToLHSDynamicValue(
    llvm::Value *lhsPtr, [[maybe_unused]] const std::string &_,
    llvm::Value *rhsValue, CodeGenerationContext *context,
    llvm::IRBuilder<> *&Builder) {

  llvm::StructType *dynamicValueStructType = llvm::StructType::getTypeByName(
      *context->getContext(), DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);
  llvm::Value *insertedDataValue = nullptr;

  TypeMapper *_typeMapper = context->getMapper().get();

  if (_typeMapper->isNirastValue(rhsValue) ||
      rhsValue->getType() == llvm::Type::getVoidTy(*context->getContext())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::NIRAST);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue = Builder->CreateInsertValue(
        UndefDynamicVal, typeTag, {0}, "insertedTagValue");

    // For Nirast, the value doesn't matter, so we store 0.
    llvm::Value *nilValue = llvm::ConstantInt::get(
        llvm::Type::getInt64Ty(*context->getContext()), 0);

    insertedDataValue = Builder->CreateInsertValue(insertedTagValue, nilValue,
                                                   {1}, "insertedDataValue");
  } else if (_typeMapper->isStringType(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::STRING);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0

    llvm::Value *pointerToStoreAsInt64 = Builder->CreatePtrToInt(
        rhsValue, llvm::Type::getInt64Ty(*context->getContext()), "ptr_as_i64");

    insertedDataValue = Builder->CreateInsertValue(
        insertedTagValue, pointerToStoreAsInt64, {1}, "insertedDataValue");

  } else if (_typeMapper->isInt32Type(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT32);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0
    llvm::Value *int32AsInt64 = Builder->CreateIntCast(
        rhsValue, llvm::Type::getInt64Ty(*context->getContext()), true);

    insertedDataValue = Builder->CreateInsertValue(
        insertedTagValue, int32AsInt64, {1}, "insertedDataValue");
  } else if (_typeMapper->isInt64Type(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT64);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0

    insertedDataValue = Builder->CreateInsertValue(insertedTagValue, rhsValue,
                                                   {1}, "insertedDataValue");
  } else if (_typeMapper->isBoolType(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::BOOLEAN);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0

    llvm::Value *int1AsInt64 = Builder->CreateIntCast(
        rhsValue, llvm::Type::getInt64Ty(*context->getContext()), true);

    insertedDataValue = Builder->CreateInsertValue(
        insertedTagValue, int1AsInt64, {1}, "insertedDataValue");
  } else if (_typeMapper->isInt8Type(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT8);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0

    llvm::Value *int8AsInt64 = Builder->CreateIntCast(
        rhsValue, llvm::Type::getInt64Ty(*context->getContext()), true);

    insertedDataValue = Builder->CreateInsertValue(
        insertedTagValue, int8AsInt64, {1}, "insertedDataValue");
  } else if (_typeMapper->isFloatType(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT32);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0
    llvm::Value *float32BitsAsInt32 = Builder->CreateBitCast(
        rhsValue, llvm::Type::getInt32Ty(*context->getContext()));
    llvm::Value *float32BitsAsInt64 = Builder->CreateZExt(
        float32BitsAsInt32, llvm::Type::getInt64Ty(*context->getContext()));

    insertedDataValue = Builder->CreateInsertValue(
        insertedTagValue, float32BitsAsInt64, {1}, "insertedDataValue");
  } else if (_typeMapper->isDoubleType(rhsValue->getType())) {

    llvm::ConstantInt *typeTag =
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT64);

    llvm::Value *UndefDynamicVal =
        llvm::UndefValue::get(dynamicValueStructType);

    llvm::Value *insertedTagValue =
        Builder->CreateInsertValue(UndefDynamicVal, typeTag, {0},
                                   "insertedTagValue"); // Insert tag at index 0

    llvm::Value *float64AsInt64 = Builder->CreateBitCast(
        rhsValue, llvm::Type::getInt64Ty(*context->getContext()),
        "float64AsInt64");

    insertedDataValue = Builder->CreateInsertValue(
        insertedTagValue, float64AsInt64, {1}, "insertedDataValue");
  } else {
    context->getLogger()->LogError(
        "Unsupported type for assignment: " +
        _typeMapper->getLLVMTypeName(
            _typeMapper->mapLLVMTypeToCustomType(rhsValue->getType())));
    return nullptr;
  }

  llvm::StoreInst *Store = Builder->CreateStore(insertedDataValue, lhsPtr);
  Store->setAlignment(llvm::Align(8));

  return rhsValue;
}

void assignRHSDynamicValueToLHSDynamicValue(llvm::Value *lhsDynamicValue,
                                            llvm::Value *rhsDynamicValue,
                                            CodeGenerationContext *context,
                                            llvm::IRBuilder<> *&Builder) {
  generateDynamicDispatch(
      rhsDynamicValue, context, Builder, [&](llvm::Value *rhsValue) {
        assignRHSValueToLHSDynamicValue(lhsDynamicValue, "lhsDynamicValue",
                                        rhsValue, context, Builder);
      });
}

void assignRHSDynamicValueToLHSVariable(llvm::Value *lhsVariable,
                                        llvm::Type *lhsType,
                                        llvm::Value *rhsDynamicValue,
                                        CodeGenerationContext *context,
                                        llvm::IRBuilder<> *&Builder) {
  generateDynamicDispatch(
      rhsDynamicValue, context, Builder, [&](llvm::Value *rhsValue) {
        Builder->CreateStore(
            FlowWing::EXPLICIT_CONVERTER::explicitConvertLLVMValueTo(
                rhsValue, lhsType, context),
            lhsVariable);
      });
}

std::pair<llvm::Value *, llvm::Value *>
getDynamicStoredValueAndType(llvm::Value *&dynamicValue,
                             CodeGenerationContext *&context,
                             llvm::IRBuilder<> *&Builder) {

  llvm::Value *loadedValue = Builder->CreateLoad(
      llvm::StructType::getTypeByName(*context->getContext(),
                                      DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE),
      dynamicValue, "loadedValue");

  llvm::Value *typeTag =
      Builder->CreateExtractValue(loadedValue, {0}, "typeTag");

  llvm::Value *valueStorage =
      Builder->CreateExtractValue(loadedValue, {1}, "valueStorage");

  return {valueStorage, typeTag};
}

llvm::Value *
generateDynamicDispatch(llvm::Value *dynamicValue,
                        CodeGenerationContext *context,
                        llvm::IRBuilder<> *&Builder,
                        const std::function<void(llvm::Value *)> &handler) {
  context->getValueStackHandler()->popAll();

  llvm::Function *parentFunc = Builder->GetInsertBlock()->getParent();

  struct {
    llvm::BasicBlock *checkBB;
    llvm::BasicBlock *handleBB;
    DYNAMIC_VALUE::TYPE::VALUE_TYPE type;
  } checkAndHandleBlocks[] = {
      {llvm::BasicBlock::Create(*context->getContext(), "check.string",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.string",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::STRING},

      {llvm::BasicBlock::Create(*context->getContext(), "check.int32",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.int32",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT32},

      {llvm::BasicBlock::Create(*context->getContext(), "check.int64",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.int64",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT64},

      {llvm::BasicBlock::Create(*context->getContext(), "check.float32",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.float32",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT32},

      {llvm::BasicBlock::Create(*context->getContext(), "check.float64",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.float64",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT64},

      {llvm::BasicBlock::Create(*context->getContext(), "check.boolean",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.boolean",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::BOOLEAN},

      {llvm::BasicBlock::Create(*context->getContext(), "check.int8",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.int8",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT8},

      {llvm::BasicBlock::Create(*context->getContext(), "check.nirast",
                                parentFunc),
       llvm::BasicBlock::Create(*context->getContext(), "handle.nirast",
                                parentFunc),
       DYNAMIC_VALUE::TYPE::VALUE_TYPE::NIRAST},
  };

  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*context->getContext(), "merge", parentFunc);

  auto [valueStorage, typeTag] =
      getDynamicStoredValueAndType(dynamicValue, context, Builder);

  Builder->CreateBr(checkAndHandleBlocks[0].checkBB);

  const int numTypes =
      sizeof(checkAndHandleBlocks) / sizeof(checkAndHandleBlocks[0]);

  for (int i = 0; i < numTypes; i++) {

    //? Check the type
    Builder->SetInsertPoint(checkAndHandleBlocks[i].checkBB);
    llvm::Value *isType = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               checkAndHandleBlocks[i].type));
    Builder->CreateCondBr(
        isType, checkAndHandleBlocks[i].handleBB,
        i == numTypes - 1 ? mergeBB : checkAndHandleBlocks[i + 1].checkBB);

    //? Handle the type
    Builder->SetInsertPoint(checkAndHandleBlocks[i].handleBB);
    llvm::Value *castedValue = VALUE_CASTER::castToType(
        valueStorage, checkAndHandleBlocks[i].type, context, Builder);
    DEBUG_LOG("casted value type",
              context->getMapper()->getLLVMTypeName(castedValue->getType()));
    handler(castedValue);
    Builder->CreateBr(mergeBB);
  }

  Builder->SetInsertPoint(mergeBB);

  return nullptr;
}

} // namespace DYNAMIC_VALUE_HANDLER