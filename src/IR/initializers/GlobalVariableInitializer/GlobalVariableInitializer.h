#ifndef __GLOBAL_VARIABLE_INITIALIZER_H__
#define __GLOBAL_VARIABLE_INITIALIZER_H__

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include "../../context/CodeGenerationContext.h"

class GlobalVariableInitializer {
public:
  GlobalVariableInitializer(CodeGenerationContext *codeGenerationContext);

  void initialize();

private:
  llvm::Module *TheModule;
  llvm::LLVMContext *TheContext;
  CodeGenerationContext *_codeGenerationContext;

  llvm::Type *i8Type;
  llvm::Type *i32Type;

  void initializeTrue();
  void initializeFalse();
  void initializeI8Null();
  void initializeBreakCount();
  void initializeContinueCount();
  void initializeErrorCount();
  void initializeDynamicValueTypes();
};

#endif // __GLOBAL_VARIABLE_INITIALIZER_H__