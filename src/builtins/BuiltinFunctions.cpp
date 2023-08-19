
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

  //  argument using puts
  llvm::Value *arg = printFunc->arg_begin();
  llvm::FunctionType *putsFuncType = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(context),
      {llvm::Type::getInt8PtrTy(context)}, // Argument type for puts
      false);
  llvm::Function *putsFunc = llvm::Function::Create(
      putsFuncType, llvm::Function::ExternalLinkage, "puts", module);
  builder.CreateCall(putsFunc, {arg});
  builder.CreateRetVoid();

  return printFunc;
}

} // namespace Builtins