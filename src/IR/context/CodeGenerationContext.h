#ifndef CODEGENERATIONCONTEXT_H
#define CODEGENERATIONCONTEXT_H

#include "../TypeBuilder/StructTypeBuilder/StructTypeBuilder.h"
#include "../handlers/alloca/AllocaChain/AllocaChain.h"
#include "../handlers/alloca/AllocaTable/AllocaTable.h"
#include "../handlers/value/NamedValueTable/NamedValueTable.h"
#include "../handlers/value/ValueChain/ValueChain.h"
#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

class BoundFunctionDeclaration;
class CodeGenerationContext {
public:
  CodeGenerationContext(DiagnosticHandler *diagnosticHandler,
                        const std::string sourceFileName);

  std::unique_ptr<llvm::IRBuilder<>> &getBuilder();
  std::unique_ptr<llvm::Module> &getModule();
  std::unique_ptr<llvm::LLVMContext> &getContext();
  std::unique_ptr<TypeMapper> &getMapper();
  std::unique_ptr<LLVMLogger> &getLogger();
  std::unique_ptr<ValueChain> &getNamedValueChain();
  std::unique_ptr<AllocaChain> &getAllocaChain();

  // TODO: Refactor this to a better place
  std::stack<std::pair<Utils::type, int8_t>> &getReturnAllocaStack();
  std::unordered_map<std::string, int8_t> &getRecursiveFunctionsMap();
  std::map<std::string, BoundFunctionDeclaration *> &getBoundedUserFunctions();
  std::unordered_map<std::string, uint64_t> &getGlobalTypeMap();

  std::string getPrefixedName(std::string name);
  const std::string &getSourceFileName() const;

  std::unique_ptr<StructTypeBuilder> &getDynamicType();

  DiagnosticHandler *getDiagnosticHandler() const;

  void addBoundedUserFunction(std::string name,
                              BoundFunctionDeclaration *functionDeclaration);

  // TODO: Refactor this to a better place
  llvm::Value *isCountZero(const std::string name, llvm::Type *ty);
  // TODO: Refactor this to a better place
  void decrementCountIfNotZero(const std::string name);
  // TODO: Refactor this to a better place
  void incrementCount(const std::string name);
  // TODO: Refactor this to a better place
  llvm::Constant *createConstantFromValue(llvm::Value *myValue);

  void callREF(const std::string &error);

private:
  std::unique_ptr<llvm::LLVMContext> _context;
  std::unique_ptr<llvm::Module> _module;
  std::unique_ptr<llvm::IRBuilder<>> _builder;
  std::unique_ptr<TypeMapper> _typeMapper;
  std::unique_ptr<LLVMLogger> _llvmLogger;

  std::unique_ptr<ValueChain> _namedValueChain;
  std::unique_ptr<AllocaChain> _allocaChain;
  std::unique_ptr<StructTypeBuilder> _dynamicType;

  DiagnosticHandler *_diagnosticHandler;
  std::string _sourceFileName;

  std::stack<std::pair<Utils::type, int8_t>> _returnAllocaStack;
  std::unordered_map<std::string, int8_t> _recursiveFunctionsMap;

  std::map<std::string, BoundFunctionDeclaration *> _boundedUserFunctions;
  std::unordered_map<std::string, uint64_t> _globalTypeMap;
};

#endif // CODEGENERATIONCONTEXT_H