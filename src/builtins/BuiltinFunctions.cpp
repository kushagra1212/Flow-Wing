
// BuiltinFunctions.cpp
#include "BuiltinFunctions.h"
namespace Builtins {
llvm::Function *createPrintFunction(llvm::Module *module) {
  llvm::LLVMContext &context = module->getContext();

  // function type
  llvm::FunctionType *printFuncType = llvm::FunctionType::get(
      llvm::Type::getVoidTy(context),
      {llvm::Type::getInt8PtrTy(context), llvm::Type::getInt1Ty(context)},
      // String argument type

      false);

  //  function
  llvm::Function *printFunc = llvm::Function::Create(
      printFuncType, llvm::Function::ExternalLinkage, "print", module);

  // function body
  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(context, "entry", printFunc);
  llvm::BasicBlock *exitBlock =
      llvm::BasicBlock::Create(context, "exit", printFunc);
  llvm::BasicBlock *withoutnewlineBlock =
      llvm::BasicBlock::Create(context, "withoutnewline", printFunc);
  llvm::BasicBlock *newlineBlock =
      llvm::BasicBlock::Create(context, "newline", printFunc);
  llvm::IRBuilder<> builder(context);
  builder.SetInsertPoint(entryBlock);
  llvm::FunctionType *printfFuncType;
  llvm::Function *printfFunc;
  llvm::GlobalVariable *formatStrGlobal;
  llvm::Value *formatStrPtr; // argument using printf

  printfFuncType = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(context),
      {llvm::Type::getInt8PtrTy(context)}, // Argument type for printf
      true);                               // Variadic function
  printfFunc = llvm::Function::Create(
      printfFuncType, llvm::Function::ExternalLinkage, "printf", module);
  // get print function args

  llvm::Value *arg = printFunc->arg_begin();
  llvm::Value *newline = printFunc->arg_begin() + 1;

  builder.CreateCondBr(newline, newlineBlock, withoutnewlineBlock);

  builder.SetInsertPoint(newlineBlock);

  // Create format string constant only once

  formatStrGlobal = module->getGlobalVariable("formatStrprintfnewline");

  if (!formatStrGlobal) {
    llvm::Constant *formatStr =
        llvm::ConstantDataArray::getString(context, "%s\n");
    formatStrGlobal = new llvm::GlobalVariable(
        *module, formatStr->getType(), true, llvm::GlobalValue::PrivateLinkage,
        formatStr, "formatStrprintfnewline");
  }

  formatStrPtr =
      builder.CreateBitCast(formatStrGlobal, llvm::Type::getInt8PtrTy(context));

  // Call printf
  llvm::Value *args[] = {formatStrPtr, arg};
  builder.CreateCall(printfFunc, args);

  builder.CreateBr(exitBlock);

  builder.SetInsertPoint(withoutnewlineBlock);

  // Create format string constant only once

  formatStrGlobal = module->getGlobalVariable("formatStrprintf");

  if (!formatStrGlobal) {
    llvm::Constant *formatStr =
        llvm::ConstantDataArray::getString(context, "%s");
    formatStrGlobal = new llvm::GlobalVariable(
        *module, formatStr->getType(), true, llvm::GlobalValue::PrivateLinkage,
        formatStr, "formatStrprintf");
  }

  formatStrPtr =
      builder.CreateBitCast(formatStrGlobal, llvm::Type::getInt8PtrTy(context));

  // Call printf
  llvm::Value *args2[] = {formatStrPtr, arg};
  builder.CreateCall(printfFunc, args2);

  builder.CreateBr(exitBlock);

  builder.SetInsertPoint(exitBlock);

  builder.CreateRetVoid();

  return printFunc;
}
} // namespace Builtins
