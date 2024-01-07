#ifndef __TYPE_CONVERTER_BASE_H__
#define __TYPE_CONVERTER_BASE_H__

#include <llvm/IR/LLVMContext.h>

#include "../constants/FlowWingIRConstants.h"
#include "../context/CodeGenerationContext.h"
#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
using namespace FLOWWING::IR::CONSTANTS;

class TypeConverterBase {
 public:
  CodeGenerationContext *_codeGenerationContext;
  llvm::IRBuilder<> *_builder;
  llvm::Module *_module;
  TypeMapper *_mapper;
  LLVMLogger *_logger;
  llvm::LLVMContext *_llvmContext;

  TypeConverterBase(CodeGenerationContext *context)
      : _module(context->getModule().get()),
        _mapper(context->getMapper().get()),
        _logger(context->getLogger().get()),
        _builder(context->getBuilder().get()),
        _llvmContext(context->getContext().get()),
        _codeGenerationContext(context){};

  virtual llvm::Value *convertExplicit(llvm::Value *value) = 0;

  virtual llvm::Value *convertImplicit(llvm::Value *value) = 0;
};

#endif  // __TYPE_CONVERTER_BASE_H__
