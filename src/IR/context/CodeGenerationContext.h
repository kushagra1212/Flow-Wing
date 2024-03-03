#ifndef CODEGENERATIONCONTEXT_H
#define CODEGENERATIONCONTEXT_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include "../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../TypeBuilder/StructTypeBuilder/StructTypeBuilder.h"
#include "../handlers/CustomTypeStatement/CustomTypeStatementChain/CustomTypeStatementChain.h"
#include "../handlers/CustomTypeStatement/CustomTypeStatementTable/CustomTypeStatementTable.h"
#include "../handlers/alloca/AllocaChain/AllocaChain.h"
#include "../handlers/alloca/AllocaTable/AllocaTable.h"
#include "../handlers/type/TypeChain/TypeChain.h"
#include "../handlers/type/TypeTable/TypeTable.h"
#include "../handlers/value/NamedValueTable/NamedValueTable.h"
#include "../handlers/value/ValueChain/ValueChain.h"
#include "../irGen/Types/ArgsTypeHandler.h"
#include "../irGen/Types/ReturnTypeHandler.h"
#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/Support/TargetSelect.h"
#include "utils/ValueStack/ValueStackHandler.h"

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
  std::unique_ptr<TypeChain> &getTypeChain();
  std::unique_ptr<CustomTypeStatementChain> &getCustomTypeChain();

  std::unique_ptr<ArgsTypeHandler> &getArgsTypeHandler();
  std::unique_ptr<ReturnTypeHandler> &getReturnTypeHandler();

  // TODO: Refactor this to a better place
  std::stack<int8_t> &getReturnAllocaStack();
  std::unordered_map<std::string, int8_t> &getRecursiveFunctionsMap();
  std::unordered_map<std::string, BoundFunctionDeclaration *> &
  getBoundedUserFunctions();
  std::unordered_map<std::string, uint64_t> &getGlobalTypeMap();

  std::string getPrefixedName(std::string name);
  const std::string &getSourceFileName() const;

  const std::unique_ptr<StructTypeBuilder> &getDynamicType();

  inline std::unique_ptr<ValueStackHandler> &getValueStackHandler() {
    return _valueStackHandler;
  }

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

  void setArraySizeMetadata(llvm::Value *array,
                            const std::vector<uint64_t> &sizes);

  void getArraySizeMetadata(llvm::Value *array, std::vector<uint64_t> &sizes);

  void setArrayElementTypeMetadata(llvm::Value *array, llvm::Type *elementType);

  void setMetadata(const std::string kind, llvm::Value *array,
                   const std::string &metaData);

  void getMetaData(const std::string kind, llvm::Value *array,
                   std::string &metaData);
  llvm::Type *getArrayElementTypeMetadata(llvm::Value *array);
  void getMultiArrayType(llvm::ArrayType *&arrayType, llvm::Constant *&def,
                         const std::vector<uint64_t> &actualSizes,
                         llvm::Type *elementType);

  void getRetrunedArrayType(llvm::Function *F, llvm::ArrayType *&arrayType,
                            llvm::Type *&arrayElementType,
                            std::vector<uint64_t> &actualSizes);

  void getReturnedObjectType(llvm::Function *F, llvm::StructType *&objectType);

 private:
  std::unique_ptr<llvm::LLVMContext> _context;
  std::unique_ptr<llvm::Module> _module;
  std::unique_ptr<llvm::IRBuilder<>> _builder;
  std::unique_ptr<TypeMapper> _typeMapper;
  std::unique_ptr<LLVMLogger> _llvmLogger;

  std::unique_ptr<ValueChain> _namedValueChain;
  std::unique_ptr<AllocaChain> _allocaChain;
  std::unique_ptr<TypeChain> _typeChain;
  std::unique_ptr<CustomTypeStatementChain> _customTypeExpressionChain;
  std::unique_ptr<ValueStackHandler> _valueStackHandler;

  std::unique_ptr<ArgsTypeHandler> _argsTypeHandler;
  std::unique_ptr<ReturnTypeHandler> _returnTypeHandler;
  std::unique_ptr<StructTypeBuilder> _dynamicType;
  DiagnosticHandler *_diagnosticHandler;
  std::string _sourceFileName;

  std::stack<int8_t> _returnAllocaStack;
  std::unordered_map<std::string, int8_t> _recursiveFunctionsMap;

  std::unordered_map<std::string, BoundFunctionDeclaration *>
      _boundedUserFunctions;
  std::unordered_map<std::string, uint64_t> _globalTypeMap;
};

#endif  // CODEGENERATIONCONTEXT_H