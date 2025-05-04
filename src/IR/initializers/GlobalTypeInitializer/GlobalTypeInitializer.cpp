#include "GlobalTypeInitializer.h"

GlobalTypeInitializer::GlobalTypeInitializer(
    CodeGenerationContext *codeGenerationContext)
    : _codeGenerationContext(codeGenerationContext),
      TheModule(codeGenerationContext->getModule().get()),
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
