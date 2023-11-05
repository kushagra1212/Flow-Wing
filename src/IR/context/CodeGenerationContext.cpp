#include "CodeGenerationContext.h"

CodeGenerationContext ::CodeGenerationContext(llvm::IRBuilder<> *builder,
                                              llvm::Module *module,
                                              llvm::LLVMContext *context,
                                              TypeMapper *mapper,
                                              LLVMLogger *logger,
                                              std::string sourceFileName)
    : _builder(builder), _module(module), _context(context), _mapper(mapper),
      _logger(logger), _sourceFileName(sourceFileName){};

llvm::IRBuilder<> *CodeGenerationContext::getBuilder() const {
  return _builder;
}

llvm::Module *CodeGenerationContext::getModule() const { return _module; }

TypeMapper *CodeGenerationContext::getMapper() const { return _mapper; }

LLVMLogger *CodeGenerationContext::getLogger() const { return _logger; }

llvm::LLVMContext *CodeGenerationContext::getContext() const {
  return _context;
}

std::string CodeGenerationContext::getPrefixedName(std::string name) const {
  return this->_sourceFileName + "_" + name;
}