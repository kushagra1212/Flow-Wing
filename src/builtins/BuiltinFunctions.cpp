
// BuiltinFunctions.cpp
#include "BuiltinFunctions.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
namespace Builtins {
llvm::Function *createPrintFunction(llvm::Module *module) {
  llvm::LLVMContext &context = module->getContext();

  // function type
  llvm::FunctionType *printFuncType = llvm::FunctionType::get(
      llvm::Type::getVoidTy(context),
      llvm::Type::getInt8PtrTy(context), // String argument type
      false);

  //  function
  llvm::Function *printFunc = llvm::Function::Create(
      printFuncType, llvm::Function::ExternalLinkage, "print", module);

  // function body
  llvm::BasicBlock *entryBlock =
      llvm::BasicBlock::Create(context, "entry", printFunc);
  llvm::IRBuilder<> builder(context);
  builder.SetInsertPoint(entryBlock);

  // argument using printf
  llvm::Value *arg = printFunc->arg_begin();
  llvm::FunctionType *printfFuncType = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(context),
      {llvm::Type::getInt8PtrTy(context)}, // Argument type for printf
      true);                               // Variadic function
  llvm::Function *printfFunc = llvm::Function::Create(
      printfFuncType, llvm::Function::ExternalLinkage, "printf", module);

  // Create format string constant
  llvm::Constant *formatStr = llvm::ConstantDataArray::getString(context, "%s");
  llvm::GlobalVariable *formatStrGlobal = new llvm::GlobalVariable(
      *module, formatStr->getType(), true, llvm::GlobalValue::PrivateLinkage,
      formatStr, ".str");

  llvm::Value *formatStrPtr =
      builder.CreateBitCast(formatStrGlobal, llvm::Type::getInt8PtrTy(context));

  // Call printf
  llvm::Value *args[] = {formatStrPtr, arg};
  builder.CreateCall(printfFunc, args);
  builder.CreateRetVoid();

  return printFunc;
}

} // namespace Builtins