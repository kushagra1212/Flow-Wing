#ifndef __TYPE_CONVERTER_BASE_H__
#define __TYPE_CONVERTER_BASE_H__

#include "../constants/FlowWingIRConstants.h"
#include "../context/CodeGenerationContext.h"
#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <llvm/IR/LLVMContext.h>
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
      : _module(context->getModule()), _mapper(context->getMapper()),
        _logger(context->getLogger()), _builder(context->getBuilder()),
        _llvmContext(context->getContext()), _codeGenerationContext(context){};

  virtual llvm::Value *convertExplicit(llvm::Value *value) = 0;

  virtual llvm::Value *convertImplicit(llvm::Value *value) = 0;
};

#endif // __TYPE_CONVERTER_BASE_H__