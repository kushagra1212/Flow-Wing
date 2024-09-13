#ifndef CODEGENERATIONCONTEXT_H
#define CODEGENERATIONCONTEXT_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include "../../utils/BuiltInFunction/BuiltInFunction.h"
#include "../TypeBuilder/StructTypeBuilder/StructTypeBuilder.h"
#include "../handlers/alloca/AllocaChain/AllocaChain.h"
#include "../handlers/alloca/AllocaTable/AllocaTable.h"
#include "../handlers/value/NamedValueTable/NamedValueTable.h"
#include "../handlers/value/ValueChain/ValueChain.h"
#include "../irGen/Types/ArgsTypeHandler.h"
#include "../irGen/Types/Class.h"
#include "../irGen/Types/Function.h"
#include "../irGen/Types/ReturnTypeHandler.h"
#include "../irGen/Types/Type.h"
#include "../logger/LLVMLogger.h"
#include "../mappers/TypeMapper/TypeMapper.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "utils/ValueStack/ValueStackHandler.h"
//! TODO: Refactor Import
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Type.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Pass.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/Transforms/Scalar.h"
// ExecutionEngine
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/SourceMgr.h>

#include "llvm//IR/Value.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/raw_ostream.h"
// JIT
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/raw_ostream.h>
//!
class TypeMapper;
class BoundFunctionDeclaration;
class CodeGenerationContext {
 public:
  CodeGenerationContext(FLowWing::DiagnosticHandler *diagnosticHandler,
                        const std::string sourceFileName);

  std::unique_ptr<llvm::IRBuilder<>> &getBuilder();
  std::unique_ptr<llvm::Module> &getModule();
  std::unique_ptr<llvm::LLVMContext> &getContext();
  std::unique_ptr<TypeMapper> &getMapper();
  std::unique_ptr<LLVMLogger> &getLogger();

  std::unique_ptr<ValueChain> &getNamedValueChain();
  std::unique_ptr<AllocaChain> &getAllocaChain();

  std::unique_ptr<ArgsTypeHandler> &getArgsTypeHandler();
  std::unique_ptr<ReturnTypeHandler> &getReturnTypeHandler();

  // TODO: Refactor this to a better place
  std::stack<int8_t> &getReturnAllocaStack();
  std::unordered_map<std::string, int8_t> &getRecursiveFunctionsMap();
  std::unordered_map<std::string, BoundFunctionDeclaration *> &
  getBoundedUserFunctions();

  std::string getPrefixedName(std::string name);
  const std::string &getSourceFileName() const;

  const std::unique_ptr<StructTypeBuilder> &getDynamicType();

  inline std::unique_ptr<ValueStackHandler> &getValueStackHandler() {
    return _valueStackHandler;
  }

  FLowWing::DiagnosticHandler *getDiagnosticHandler() const;

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
  void getMultiArrayTypeForGlobal(llvm::ArrayType *&arrayType,
                                  llvm::Constant *&def,
                                  const std::vector<uint64_t> &actualSizes,
                                  llvm::Type *elementType);
  void getMultiArrayType(llvm::ArrayType *&arrayType,
                         const std::vector<uint64_t> &actualSizes,
                         llvm::Type *elementType);
  void getRetrunedArrayType(llvm::Function *F, llvm::ArrayType *&arrayType,
                            llvm::Type *&arrayElementType,
                            std::vector<uint64_t> &actualSizes);

  void getReturnedObjectType(llvm::Function *F, llvm::StructType *&objectType);

  int8_t verifyArrayType(llvm::ArrayType *lhsType, llvm::ArrayType *rhsType,
                         std::string inExp = " in assignment expression");
  int8_t verifyStructType(llvm::StructType *lhsType, llvm::StructType *rhsType,
                          std::string inExp = " in assignment expression");
  int8_t verifyType(llvm::Type *lhsType, llvm::Type *rhsType,
                    std::string inExp = " in assignment expression");

  int8_t verifyType(const std::vector<llvm::Type *> &lhsTypes,
                    const std::vector<llvm::Type *> &rhsTypes,
                    const std::string &inExp);

  llvm::Value *createMemoryGetPtr(llvm::Type *type, std::string variableName,
                                  BinderKindUtils::MemoryKind memoryKind,
                                  llvm::Constant *initialValue = nullptr);

  void getReturnedPrimitiveType(llvm::Function *F, llvm::Type *&type);
  inline auto createArraySizesAndArrayElementType(
      std::vector<uint64_t> &actualSizes, llvm::Type *&arrayElementType)
      -> void {
    while (llvm::ArrayType *arrayType =
               llvm::dyn_cast<llvm::ArrayType>(arrayElementType)) {
      actualSizes.push_back(arrayType->getNumElements());
      arrayElementType = arrayType->getElementType();
    }
  }

  inline auto setCurrentClassName(std::string className) -> void {
    _currentClassName = className;
  }

  inline auto getCurrentClassName() -> std::string { return _currentClassName; }

  inline auto resetCurrentClassName() -> void { _currentClassName = ""; }

  auto createVTableMapEntry(
      std::unordered_map<
          std::string, std::tuple<llvm::FunctionType *, uint64_t, std::string>>
          &vTableElementsMap,
      std::string className, uint64_t &index) -> void;

  // verifiers
  void verifyFunction(llvm::Function *F, const std::string &FUNCTION_NAME);
  void verifyModule(llvm::Module *M);

  inline auto isValidClassType(llvm::StructType *type) -> bool {
    return this->_classTypes.find((type->getStructName().str())) !=
               this->_classTypes.end() &&
           this->_classTypes[(type->getStructName().str())];
  }

  inline auto isClassMemberFunction(const std::string &funName) -> bool {
    return this->_classTypes.find(funName.substr(
               0,
               funName.find(FLOWWING::UTILS::CONSTANTS::MEMBER_FUN_PREFIX))) !=
           this->_classTypes.end();
  }

  inline auto isCustomTypeExists(const std::string &typeName) -> bool {
    return this->_typesMap.find(typeName) != this->_typesMap.end();
  }

  inline auto getFlowWingType(const std::string &typeName) -> FlowWing::Type {
    const bool isClassType =
        this->_classTypes.find(typeName) != this->_classTypes.end();
    if (!isCustomTypeExists(typeName) && !isClassType) {
      this->getLogger()->LogError("Type " + typeName +
                                  " is not defined in this scope");

      return FlowWing::Type();
    }

    return this->_typesMap[typeName];
  }

  inline auto addClass(const std::string &name,
                       std::unique_ptr<Class> classType) -> void {
    this->_classes.push_back(std::move(classType));
    this->_classTypes[name] = this->_classes.back().get();
  }

  inline auto getTargetMachine() -> llvm::TargetMachine * {
    return this->_targetMachine;
  }

  auto getArrayTypeAsString(llvm::ArrayType *arrayType) -> std::string;

  std::unordered_map<std::string, Class *> _classTypes;
  std::unordered_map<std::string, llvm::StructType *> _classLLVMTypes;

  // custom struct types
  std::unordered_map<std::string, FlowWing::Type> _typesMap;
  std::unordered_map<std::string, std::unique_ptr<FlowWing::Function>>
      _functionTypes;

 private:
  std::unique_ptr<llvm::LLVMContext> _context;
  std::unique_ptr<llvm::Module> _module;
  std::unique_ptr<llvm::IRBuilder<>> _builder;
  std::unique_ptr<TypeMapper> _typeMapper;
  std::unique_ptr<LLVMLogger> _llvmLogger;

  std::unique_ptr<ValueChain> _namedValueChain;
  std::unique_ptr<AllocaChain> _allocaChain;
  std::unique_ptr<ValueStackHandler> _valueStackHandler;

  std::unique_ptr<ArgsTypeHandler> _argsTypeHandler;
  std::unique_ptr<ReturnTypeHandler> _returnTypeHandler;
  std::unique_ptr<StructTypeBuilder> _dynamicType;
  FLowWing::DiagnosticHandler *_diagnosticHandler;
  std::string _sourceFileName;

  std::stack<int8_t> _returnAllocaStack;
  std::unordered_map<std::string, int8_t> _recursiveFunctionsMap;

  std::unordered_map<std::string, BoundFunctionDeclaration *>
      _boundedUserFunctions;

  std::vector<std::unique_ptr<Class>> _classes;

  llvm::TargetMachine *_targetMachine = nullptr;
  std::string _currentClassName = "";
};

#endif  // CODEGENERATIONCONTEXT_H