#ifndef __FLOWWING_LLVM_VALUE_CONVERTER_H__
#define __FLOWWING_LLVM_VALUE_CONVERTER_H__

#include "../../../syntax/SyntaxKindUtils.h"
#include "../../context/CodeGenerationContext.h"
#include "../../logger/LLVMLogger.h"
#include "../../mappers/TypeMapper/TypeMapper.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

class LLVMValueConverter {
 public:
  LLVMValueConverter(CodeGenerationContext *context);

  llvm::Value *convertToLLVMValue(std::any value,
                                  SyntaxKindUtils::SyntaxKind kind);

  llvm::Value *int32ToLLVMValue(int32_t value);
  llvm::Value *doubleToLLVMValue(double value);
  llvm::Value *boolToLLVMValue(bool value);
  llvm::Value *stringToLLVMValue(std::string value,
                                 SyntaxKindUtils::SyntaxKind kind);

 private:
  llvm::IRBuilder<> *_builder;
  llvm::Module *_module;
  TypeMapper *_mapper;
  LLVMLogger *_logger;
  llvm::LLVMContext *_llvmContext;
  CodeGenerationContext *_codeGenerationContext;
};

#endif  // __FLOWWING_LLVM_VALUE_CONVERTER_H__