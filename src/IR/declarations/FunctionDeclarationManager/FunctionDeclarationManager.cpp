#include "FunctionDeclarationManager.h"

FunctionDeclarationManager::FunctionDeclarationManager(
    CodeGenerationContext *codeGenerationContext)
    : TheModule(codeGenerationContext->getModule().get()),
      TheContext(codeGenerationContext->getContext().get()) {}

llvm::Function *
FunctionDeclarationManager::declareFunction(const std::string &functionName,
                                            llvm::FunctionType *functionType) {
  llvm::Function *function = llvm::Function::Create(
      functionType, llvm::Function::ExternalLinkage, functionName, *TheModule);

  return function;
}

llvm::Function *FunctionDeclarationManager::declarePrintFn() {

  llvm::FunctionType *printFnType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt1Ty(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::PRINT, printFnType);
}

llvm::Function *FunctionDeclarationManager::declarePrintfFn() {

  llvm::FunctionType *printFFnType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext),
                              {
                                  llvm::Type::getInt8PtrTy(*TheContext),
                              },
                              true);
  return declareFunction(INNERS::FUNCTIONS::PRINT_F, printFFnType);
}

llvm::Function *FunctionDeclarationManager::declareConcatStringsFn() {

  llvm::FunctionType *concatStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::CONCAT_STRINGS,
                         concatStringsFnType);
}

llvm::Function *FunctionDeclarationManager::declareStringLengthFn() {

  llvm::FunctionType *stringLengthFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::STRING_LENGTH, stringLengthFnType);
}

llvm::Function *FunctionDeclarationManager::declareItosFn() {

  llvm::FunctionType *itosFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt32Ty(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::ITOS, itosFnType);
}

llvm::Function *FunctionDeclarationManager::declareDtosFn() {

  llvm::FunctionType *dtosFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getDoubleTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::DTOS, dtosFnType);
}

llvm::Function *
FunctionDeclarationManager::declareGetMallocPtrOfStringConstantFn() {

  llvm::FunctionType *getMallocPtrOfStringConstantFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::GET_MALLOC_PTR_OF_STRING_CONSTANT,
                         getMallocPtrOfStringConstantFnType);
}

llvm::Function *
FunctionDeclarationManager::declareGetMallocPtrofIntConstantFn() {

  llvm::FunctionType *getMallocPtrofIntConstantFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt32Ty(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::GET_MALLOC_PTR_OF_INT_CONSTANT,
                         getMallocPtrofIntConstantFnType);
}

llvm::Function *FunctionDeclarationManager::declareCompareStringsFn() {

  llvm::FunctionType *compareStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::COMPARE_STRINGS,
                         compareStringsFnType);
}

llvm::Function *FunctionDeclarationManager::declareLessThanStringsFn() {

  llvm::FunctionType *lessThanStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::LESS_THAN_STRINGS,
                         lessThanStringsFnType);
}

llvm::Function *FunctionDeclarationManager::declareLessThanOrEqualStringsFn() {

  llvm::FunctionType *lessThanOrEqualStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::LESS_THAN_OR_EQUAL_STRINGS,
                         lessThanOrEqualStringsFnType);
}

llvm::Function *FunctionDeclarationManager::declareGreaterThanStringsFn() {

  llvm::FunctionType *greaterThanStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::GREATER_THAN_STRINGS,
                         greaterThanStringsFnType);
}

llvm::Function *
FunctionDeclarationManager::declareGreaterThanOrEqualStringsFn() {

  llvm::FunctionType *greaterThanOrEqualStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::GREATER_THAN_OR_EQUAL_STRINGS,
                         greaterThanOrEqualStringsFnType);
}

llvm::Function *FunctionDeclarationManager::declareEqualStringsFn() {

  llvm::FunctionType *equalStringsFnType =
      llvm::FunctionType::get(llvm::Type::getInt1Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext),
                               llvm::Type::getInt8PtrTy(*TheContext)},
                              false);

  return declareFunction(INNERS::FUNCTIONS::EQUAL_STRINGS, equalStringsFnType);
}

llvm::Function *FunctionDeclarationManager::declareGetInputFn() {

  llvm::FunctionType *getInputFnType =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext), {}, false);

  return declareFunction(INNERS::FUNCTIONS::GET_INPUT, getInputFnType);
}

llvm::Function *FunctionDeclarationManager::declareStringToIntFn() {

  llvm::FunctionType *stringToIntFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::STRING_TO_INT, stringToIntFnType);
}

llvm::Function *FunctionDeclarationManager::declareStringToLongFn() {

  llvm::FunctionType *stringToLongFnType =
      llvm::FunctionType::get(llvm::Type::getInt64Ty(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::STRING_TO_LONG, stringToLongFnType);
}

llvm::Function *FunctionDeclarationManager::declareStringToDoubleFn() {

  llvm::FunctionType *stringToDoubleFnType =
      llvm::FunctionType::get(llvm::Type::getDoubleTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::STRING_TO_DOUBLE,
                         stringToDoubleFnType);
}

llvm::Function *FunctionDeclarationManager::declareRaiseExceptionFn() {

  llvm::FunctionType *raiseDivisionByZeroExceptionFnType =
      llvm::FunctionType::get(llvm::Type::getVoidTy(*TheContext),
                              {llvm::Type::getInt8PtrTy(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION,
                         raiseDivisionByZeroExceptionFnType);
}

llvm::Function *FunctionDeclarationManager::declareMallocFunctionFn() {

  llvm::FunctionType *mallocFunctionFn =
      llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*TheContext),
                              {llvm::Type::getInt64Ty(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::MALLOC, mallocFunctionFn);
}

llvm::Function *FunctionDeclarationManager::declarePutChar() {

  llvm::FunctionType *putCharFnType =
      llvm::FunctionType::get(llvm::Type::getInt32Ty(*TheContext),
                              {llvm::Type::getInt32Ty(*TheContext)}, false);

  return declareFunction(INNERS::FUNCTIONS::PUT_CHAR, putCharFnType);
}

llvm::Function *FunctionDeclarationManager::declareGC_Malloc() {

  llvm::ArrayRef<llvm::Type *> gcMallocArgs = {
      llvm::Type::getInt64Ty(*TheContext)};

  llvm::FunctionType *gcMallocFnType = llvm::FunctionType::get(
      llvm::Type::getInt8PtrTy(*TheContext), gcMallocArgs, false);

  return declareFunction(INNERS::FUNCTIONS::GC_MALLOC, gcMallocFnType);
}