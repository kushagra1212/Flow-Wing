#include "GlobalVariableInitializer.h"

GlobalVariableInitializer::GlobalVariableInitializer(
    CodeGenerationContext *codeGenerationContext)
    : _codeGenerationContext(codeGenerationContext),
      TheModule(codeGenerationContext->getModule().get()),
      TheContext(codeGenerationContext->getContext().get()) {

  i8Type = llvm::Type::getInt8Ty(*TheContext);
  i32Type = llvm::Type::getInt32Ty(*TheContext);
}

void GlobalVariableInitializer::initializeTrue() {
  new llvm::GlobalVariable(
      *TheModule, llvm::ArrayType::get(i8Type, 5),
      true, // isConstant
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantDataArray::getString(*TheContext, "true\00"),
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_TRUE));
}
void GlobalVariableInitializer::initializeFalse() {
  new llvm::GlobalVariable(
      *TheModule, llvm::ArrayType::get(i8Type, 6), true,
      llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantDataArray::getString(*TheContext, "false\00"),
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_FALSE));
}

void GlobalVariableInitializer::initializeI8Null() {
  new llvm::GlobalVariable(
      *TheModule, i8Type, false, llvm::GlobalValue::ExternalLinkage,
      nullptr, // For null, you can pass nullptr as the initializer
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_NULL));
}
void GlobalVariableInitializer::initializeBreakCount() {
  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      _codeGenerationContext->getPrefixedName(FLOWWING_BREAK_COUNT));
}
void GlobalVariableInitializer::initializeContinueCount() {

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      _codeGenerationContext->getPrefixedName(FLOWWING_CONTINUE_COUNT));
}
void GlobalVariableInitializer::initializeErrorCount() {

  new llvm::GlobalVariable(
      *TheModule, i32Type, false, llvm::GlobalValue::ExternalLinkage,
      llvm::ConstantInt::get(i32Type, 0),
      _codeGenerationContext->getPrefixedName(FLOWWING_GLOBAL_ERROR_COUNT));
}