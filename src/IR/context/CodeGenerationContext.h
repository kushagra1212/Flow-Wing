#ifndef CODEGENERATIONCONTEXT_H
#define CODEGENERATIONCONTEXT_H

#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

class CodeGenerationContext {
public:
  CodeGenerationContext(llvm::IRBuilder<> *builder, llvm::Module *module,
                        llvm::LLVMContext *context, TypeMapper *mapper,
                        LLVMLogger *logger, std::string sourceFileName);

  llvm::IRBuilder<> *getBuilder() const;
  llvm::Module *getModule() const;
  TypeMapper *getMapper() const;
  LLVMLogger *getLogger() const;
  llvm::LLVMContext *getContext() const;

  std::string getPrefixedName(std::string name) const;

private:
  llvm::IRBuilder<> *_builder;
  llvm::Module *_module;
  llvm::LLVMContext *_context;
  TypeMapper *_mapper;
  LLVMLogger *_logger;
  std::string _sourceFileName;
};

#endif // CODEGENERATIONCONTEXT_H