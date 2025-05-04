#include "DynamicValueHandler.h"
namespace DYNAMIC_VALUE_HANDLER {

llvm::Value *handleAssignmentToDynamicValueVariable(
    llvm::Value *lhsPtr, const std::string &variableName, llvm::Value *rhsValue,
    CodeGenerationContext *context, llvm::IRBuilder<> *&Builder) {

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
  }

  llvm::StoreInst *Store = Builder->CreateStore(insertedDataValue, lhsPtr);
  Store->setAlignment(llvm::Align(8)); // Set alignment for the store

  return rhsValue;
}

llvm::Value *
generateDynamicDispatch(llvm::Value *dynamicValue,
                        CodeGenerationContext *context,
                        llvm::IRBuilder<> *&Builder,
                        const std::function<void(llvm::Value *)> &handler) {
  llvm::Function *parentFunc = Builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *checkStringBB = llvm::BasicBlock::Create(
      *context->getContext(), "check.string", parentFunc);
  llvm::BasicBlock *printStringBB = llvm::BasicBlock::Create(
      *context->getContext(), "handle.string", parentFunc);
  llvm::BasicBlock *checkInt32BB = llvm::BasicBlock::Create(
      *context->getContext(), "check.int32", parentFunc);
  llvm::BasicBlock *printInt32BB = llvm::BasicBlock::Create(
      *context->getContext(), "print.int32", parentFunc);
  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*context->getContext(), "merge", parentFunc);

  llvm::Value *loadedValue = Builder->CreateLoad(
      llvm::StructType::getTypeByName(*context->getContext(),
                                      DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE),
      dynamicValue, "loadedValue");

  context->getValueStackHandler()->popAll();

  llvm::Value *typeTag =
      Builder->CreateExtractValue(loadedValue, {0}, "typeTag");

  llvm::Value *valueStorage =
      Builder->CreateExtractValue(loadedValue, {1}, "valueStorage");

  Builder->CreateBr(checkStringBB);

  Builder->SetInsertPoint(checkStringBB);
  llvm::Value *isString = Builder->CreateICmpEQ(
      typeTag,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                             DYNAMIC_VALUE::TYPE::VALUE_TYPE::STRING));
  Builder->CreateCondBr(isString, printStringBB, checkInt32BB);

  Builder->SetInsertPoint(printStringBB);
  llvm::Value *loadedStringPtr = Builder->CreateIntToPtr(
      valueStorage, llvm::Type::getInt8PtrTy(*context->getContext()),
      "loadedStringPtr");
  handler(loadedStringPtr);
  Builder->CreateBr(mergeBB);

  Builder->SetInsertPoint(checkInt32BB);
  llvm::Value *isInt32 = Builder->CreateICmpEQ(
      typeTag,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->getContext()),
                             DYNAMIC_VALUE::TYPE::VALUE_TYPE::INT32));
  Builder->CreateCondBr(isInt32, printInt32BB, mergeBB);

  Builder->SetInsertPoint(printInt32BB);
  llvm::Value *int32Value = Builder->CreateIntCast(
      valueStorage, llvm::Type::getInt32Ty(*context->getContext()), true,
      "int32Value");
  handler(int32Value);
  Builder->CreateBr(mergeBB);

  Builder->SetInsertPoint(mergeBB);

  return nullptr;
}
} // namespace DYNAMIC_VALUE_HANDLER