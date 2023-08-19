#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include <llvm/IR/Module.h>

namespace Builtins {

// Declare the prototype for creating the print function
llvm::Function *createPrintFunction(llvm::Module *module);

// You can declare prototypes for other built-in functions here

} // namespace Builtins

#endif // BUILTIN_FUNCTIONS_H
