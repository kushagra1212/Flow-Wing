#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Module.h>
namespace Builtins {

// Declare the prototype for creating the print function
llvm::Function *createPrintFunction(llvm::Module *module);
llvm::Function *createGetUserInputFunction(llvm::Module *module);

// You can declare prototypes for other built-in functions here

} // namespace Builtins

#endif // BUILTIN_FUNCTIONS_H
