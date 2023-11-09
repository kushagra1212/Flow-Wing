#ifndef CODEGENERATIONCONTEXT_H
#define CODEGENERATIONCONTEXT_H

#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

class CodeGenerationContext {
public:
  CodeGenerationContext(DiagnosticHandler *diagnosticHandler,
                        const std::string sourceFileName);

  std::unique_ptr<llvm::IRBuilder<>> &getBuilder();
  std::unique_ptr<llvm::Module> &getModule();
  std::unique_ptr<llvm::LLVMContext> &getContext();
  std::unique_ptr<TypeMapper> &getMapper();
  std::unique_ptr<LLVMLogger> &getLogger();

  std::string getPrefixedName(std::string name);
  const std::string &getSourceFileName() const;

  DiagnosticHandler *getDiagnosticHandler() const;

private:
  std::unique_ptr<llvm::LLVMContext> _context;
  std::unique_ptr<llvm::Module> _module;
  std::unique_ptr<llvm::IRBuilder<>> _builder;
  std::unique_ptr<TypeMapper> _typeMapper;
  std::unique_ptr<LLVMLogger> _llvmLogger;
  DiagnosticHandler *_diagnosticHandler;
  std::string _sourceFileName;
};

#endif // CODEGENERATIONCONTEXT_H