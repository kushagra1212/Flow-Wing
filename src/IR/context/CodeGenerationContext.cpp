#include "CodeGenerationContext.h"

CodeGenerationContext ::CodeGenerationContext(
    DiagnosticHandler *diagnosticHandler, const std::string sourceFileName)
    : _sourceFileName(sourceFileName) {
  _context = std::make_unique<llvm::LLVMContext>();
  _builder = std::make_unique<llvm::IRBuilder<>>(*_context);
  _module = std::make_unique<llvm::Module>("FlowWing", *_context);

  _sourceFileName = sourceFileName;

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();

  // Assign diagnosticHandler
  _diagnosticHandler = diagnosticHandler;

  // Initialize
  _typeMapper = std::make_unique<TypeMapper>(_context.get());

  // Initialize  LLVM_Logger
  _llvmLogger = std::make_unique<LLVMLogger>(diagnosticHandler);
};

std::unique_ptr<llvm::IRBuilder<>> &CodeGenerationContext::getBuilder() {
  return _builder;
}

std::unique_ptr<llvm::Module> &CodeGenerationContext::getModule() {
  return _module;
}

std::unique_ptr<llvm::LLVMContext> &CodeGenerationContext::getContext() {
  return _context;
}

std::unique_ptr<TypeMapper> &CodeGenerationContext::getMapper() {
  return _typeMapper;
}

std::unique_ptr<LLVMLogger> &CodeGenerationContext::getLogger() {
  return _llvmLogger;
}

std::string CodeGenerationContext::getPrefixedName(std::string name) {
  return this->_sourceFileName + "_" + name;
}

const std::string &CodeGenerationContext::getSourceFileName() const {
  return this->_sourceFileName;
}

DiagnosticHandler *CodeGenerationContext::getDiagnosticHandler() const {
  return _diagnosticHandler;
}
