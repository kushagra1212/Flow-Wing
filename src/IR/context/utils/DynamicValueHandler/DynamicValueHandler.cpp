#include "DynamicValueHandler.h"
#include "ValueCaster/ValueCaster.h"
namespace DYNAMIC_VALUE_HANDLER {

llvm::Value *assignRHSValueToLHSDynamicValue(llvm::Value *lhsPtr,
                                             const std::string &variableName,
                                             llvm::Value *rhsValue,
                                             CodeGenerationContext *context,
                                             llvm::IRBuilder<> *&Builder) {

  llvm::StructType *dynamicValueStructType = llvm::StructType::getTypeByName(
      *context->getContext(), DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);
  llvm::Value *insertedDataValue = nullptr;

  if (rhsValue->getType() == llvm::Type::getInt8PtrTy(*context->getContext())) {

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

  } else if (rhsValue->getType() ==
             llvm::Type::getInt32Ty(*context->getContext())) {

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
  } else if (rhsValue->getType() ==
             llvm::Type::getInt64Ty(*context->getContext())) {

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
  } else if (rhsValue->getType() ==
             llvm::Type::getInt1Ty(*context->getContext())) {

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
  } else if (rhsValue->getType() ==
             llvm::Type::getInt8Ty(*context->getContext())) {

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
  } else if (rhsValue->getType() ==
             llvm::Type::getFloatTy(*context->getContext())) {

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
  } else if (rhsValue->getType() ==
             llvm::Type::getDoubleTy(*context->getContext())) {

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
  }

  llvm::StoreInst *Store = Builder->CreateStore(insertedDataValue, lhsPtr);
  Store->setAlignment(llvm::Align(8)); // Set alignment for the store

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
  TypeMapper *_typeMapper = context->getMapper().get();
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
  llvm::Function *parentFunc = Builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *checkStringBB = llvm::BasicBlock::Create(
      *context->getContext(), "check.string", parentFunc);
  llvm::BasicBlock *handleStringBB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.string", parentFunc);
  llvm::BasicBlock *checkInt32BB = llvm::BasicBlock::Create(
      *context->getContext(), "check.int32", parentFunc);
  llvm::BasicBlock *handleInt32BB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.int32", parentFunc);
  llvm::BasicBlock *checkInt64BB = llvm::BasicBlock::Create(
      *context->getContext(), "check.int64", parentFunc);
  llvm::BasicBlock *handleInt64BB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.int64", parentFunc);
  llvm::BasicBlock *checkFloat32BB = llvm::BasicBlock::Create(
      *context->getContext(), "check.float32", parentFunc);
  llvm::BasicBlock *handleFloat32BB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.float32", parentFunc);
  llvm::BasicBlock *checkFloat64BB = llvm::BasicBlock::Create(
      *context->getContext(), "check.float64", parentFunc);
  llvm::BasicBlock *handleFloat64BB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.float64", parentFunc);
  llvm::BasicBlock *checkBooleanBB = llvm::BasicBlock::Create(
      *context->getContext(), "check.boolean", parentFunc);
  llvm::BasicBlock *handleBooleanBB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.boolean", parentFunc);
  llvm::BasicBlock *checkInt8BB = llvm::BasicBlock::Create(
      *context->getContext(), "check.int8", parentFunc);
  llvm::BasicBlock *handleInt8BB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.int8", parentFunc);

  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*context->getContext(), "merge", parentFunc);

  auto [valueStorage, typeTag] =
      getDynamicStoredValueAndType(dynamicValue, context, Builder);

  context->getValueStackHandler()->popAll();

  Builder->CreateBr(checkStringBB);

  {
    Builder->SetInsertPoint(checkStringBB);
    llvm::Value *isString = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::STRING));
    Builder->CreateCondBr(isString, handleStringBB, checkInt32BB);
  }

  {
    Builder->SetInsertPoint(handleStringBB);
    llvm::Value *loadedStringPtr =
        VALUE_CASTER::toString(valueStorage, context, Builder);
    handler(loadedStringPtr);
    Builder->CreateBr(mergeBB);
  }

  {
    Builder->SetInsertPoint(checkInt32BB);
    llvm::Value *isInt32 = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT32));
    Builder->CreateCondBr(isInt32, handleInt32BB, checkInt64BB);
  }

  {
    Builder->SetInsertPoint(handleInt32BB);
    llvm::Value *int32Value =
        VALUE_CASTER::toInt32(valueStorage, context, Builder);
    handler(int32Value);
    Builder->CreateBr(mergeBB);
  }

  {
    Builder->SetInsertPoint(checkInt64BB);
    llvm::Value *isInt64 = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT64));
    Builder->CreateCondBr(isInt64, handleInt64BB, checkFloat32BB);
  }

  {
    Builder->SetInsertPoint(handleInt64BB);
    llvm::Value *int64Value =
        VALUE_CASTER::toInt64(valueStorage, context, Builder);
    handler(int64Value);
    Builder->CreateBr(mergeBB);
  }

  {
    Builder->SetInsertPoint(checkFloat32BB);
    llvm::Value *isFloat32 = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT32));
    Builder->CreateCondBr(isFloat32, handleFloat32BB, checkFloat64BB);
  }

  {
    Builder->SetInsertPoint(handleFloat32BB);
    llvm::Value *float32Value =
        VALUE_CASTER::toFloat(valueStorage, context, Builder);
    handler(float32Value);
    Builder->CreateBr(mergeBB);
  }

  {
    Builder->SetInsertPoint(checkFloat64BB);
    llvm::Value *isFloat64 = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::FLOAT64));
    Builder->CreateCondBr(isFloat64, handleFloat64BB, checkBooleanBB);
  }

  {
    Builder->SetInsertPoint(handleFloat64BB);
    llvm::Value *doubleValue =
        VALUE_CASTER::toDouble(valueStorage, context, Builder);
    handler(doubleValue);
    Builder->CreateBr(mergeBB);
  }

  {
    Builder->SetInsertPoint(checkBooleanBB);
    llvm::Value *isBoolean = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::BOOLEAN));
    Builder->CreateCondBr(isBoolean, handleBooleanBB, checkInt8BB);
  }

  {
    Builder->SetInsertPoint(handleBooleanBB);
    llvm::Value *booleanValue =
        VALUE_CASTER::toBoolean(valueStorage, context, Builder);
    handler(booleanValue);
    Builder->CreateBr(mergeBB);
  }

  {
    Builder->SetInsertPoint(checkInt8BB);
    llvm::Value *isInt8 = Builder->CreateICmpEQ(
        typeTag,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                               DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT8));
    Builder->CreateCondBr(isInt8, handleInt8BB, mergeBB);
  }

  {
    Builder->SetInsertPoint(handleInt8BB);
    llvm::Value *int8Value =
        VALUE_CASTER::toInt8(valueStorage, context, Builder);
    handler(int8Value);
    Builder->CreateBr(mergeBB);
  }
  Builder->SetInsertPoint(mergeBB);

  return nullptr;
}
} // namespace DYNAMIC_VALUE_HANDLER