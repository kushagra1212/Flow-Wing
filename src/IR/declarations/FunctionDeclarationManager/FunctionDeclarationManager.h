#ifndef __FUNCTION_DECLARATION_MANAGER_H__
#define __FUNCTION_DECLARATION_MANAGER_H__

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include "../../constants/FlowWingIRConstants.h"
#include "../../context/CodeGenerationContext.h"

using namespace FLOWWING::IR::CONSTANTS;

class FunctionDeclarationManager {
public:
  FunctionDeclarationManager(CodeGenerationContext *codeGenerationContext);

  llvm::Function *declarePrintFn();
  llvm::Function *declareConcatStringsFn();
  llvm::Function *declareStringLengthFn();
  llvm::Function *declareItosFn();
  llvm::Function *declareDtosFn();
  llvm::Function *declareGetMallocPtrOfStringConstantFn();
  llvm::Function *declareGetMallocPtrofIntConstantFn();
  llvm::Function *declareCompareStringsFn();
  llvm::Function *declareLessThanStringsFn();
  llvm::Function *declareLessThanOrEqualStringsFn();
  llvm::Function *declareGreaterThanStringsFn();
  llvm::Function *declareGreaterThanOrEqualStringsFn();
  llvm::Function *declareEqualStringsFn();
  llvm::Function *declareGetInputFn();
  llvm::Function *declareStringToIntFn();
  llvm::Function *declareStringToLongFn();
  llvm::Function *declareStringToDoubleFn();
  llvm::Function *declarePrintfFn();
  llvm::Function *declarePutChar();

  // GC
  llvm::Function *declareGC_Malloc();

  llvm::Function *declareRaiseExceptionFn();
  llvm::Function *declareMallocFunctionFn();

private:
  llvm::Module *TheModule;
  llvm::LLVMContext *TheContext;

  llvm::Function *declareFunction(const std::string &functionName,
                                  llvm::FunctionType *functionType);
};

#endif // __FUNCTION_DECLARATION_MANAGER_H__
