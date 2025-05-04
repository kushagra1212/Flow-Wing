#pragma once
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include "../../context/CodeGenerationContext.h"

class GlobalTypeInitializer {
public:
  GlobalTypeInitializer(CodeGenerationContext *codeGenerationContext);

  void initialize();

private:
  llvm::Module *TheModule;
  llvm::LLVMContext *TheContext;
  CodeGenerationContext *_codeGenerationContext;

  void initializeDynamicValueType();
};
