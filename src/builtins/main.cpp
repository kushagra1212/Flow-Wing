
// main.cpp
#include "BuiltinFunctions.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

int main() {
  llvm::LLVMContext context;
  llvm::Module module("built_in_module", context);

  // Create the print function and add it to the module
  Builtins::createPrintFunction(&module);
  Builtins::createGetUserInputFunction(&module);

  // Save the module to a file
  std::error_code ec;
  llvm::raw_fd_ostream dest("../../evaluator/BuiltinIRs/built_in_module.ll",
                            ec);
  module.print(dest, nullptr);

  if (!ec) {
    llvm::outs() << "LLVM IR saved to built_in_module.ll\n";
  } else {
    llvm::errs() << "Error saving LLVM IR: " << ec.message() << "\n";
  }

  return 0;
}