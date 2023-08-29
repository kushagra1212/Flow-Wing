#ifndef IR_UTILS_H
#define IR_UTILS_H

// LLVM Imports
#include "llvm/IR/Type.h"
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
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/Support/Error.h>
#include <llvm/Support/SourceMgr.h>

#include <llvm/IRReader/IRReader.h>
// ExecutionEngine
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>

#include "llvm//IR/Value.h"
#include "llvm/IR/Constants.h"

// Elang Files Import

#include "../../Common.h"
#include "../../bind/Binder/Binder.h"
#include "../../bind/Binder/BoundScopeGlobal/BoundScopeGlobal.h"
#include "../../bind/BinderKindUtils.h"
#include "../../bind/BoundAssignmentExpression/BoundAssignmentExpression.h"
#include "../../bind/BoundBinaryExpression/BoundBinaryExpression.h"
#include "../../bind/BoundBlockStatement/BoundBlockStatement.h"
#include "../../bind/BoundExpression.h"
#include "../../bind/BoundExpressionStatement/BoundExpressionStatement.h"
#include "../../bind/BoundLiteralExpression/BoundLiteralExpression.h"
#include "../../bind/BoundParenthesizedExpression/BoundParenthesizedExpression.h"
#include "../../bind/BoundStatement/BoundStatement.h"
#include "../../bind/BoundUnaryExpression/BoundUnaryExpression.h"
#include "../../bind/BoundVariableExpression/BoundVariableExpression.h"
#include "../../syntax/CompilationUnitSyntax.h"

#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
// JIT
#include <llvm/ExecutionEngine/Orc/LLJIT.h>

#include "../llvm/IRGenerator.h"

#include <llvm/Support/raw_ostream.h>
#include <sstream>
namespace IRUtils {
llvm::Value *getLLVMValue(std::any value, llvm::Module *TheModule,
                          llvm::LLVMContext *TheContext,
                          llvm::IRBuilder<> *Builder);

size_t calculateStringLength(llvm::Value *strPtr, llvm::Module *TheModule,
                             llvm::IRBuilder<> *Builder);

std::string getString(BoundExpression *node);

std::string valueToString(llvm::Value *val);

llvm::Value *convertToString(llvm::Value *val, llvm::IRBuilder<> *Builder);
llvm::Value *addNewLineCharacter(llvm::Value *value, llvm::IRBuilder<> *Builder,
                                 bool isNewLine);
llvm::Value *concatenateStrings(llvm::Value *lhs, llvm::Value *rhs,
                                llvm::Module *TheModule,
                                llvm::IRBuilder<> *Builder);
llvm::Value *convertStringToi8Ptr(std::string stringValue,
                                  llvm::IRBuilder<> *Builder);
llvm::Type *getTypeFromAny(std::any value, llvm::LLVMContext *TheContext);

bool isStringType(llvm::Type *type);

bool isIntType(llvm::Type *type);

bool isBoolType(llvm::Type *type);

bool isDoubleType(llvm::Type *type);

llvm::Value *convertToDouble(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *convertToInt(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *convertToBool(llvm::Value *val, llvm::IRBuilder<> *Builder);

llvm::Value *getResultFromBinaryOperationOnDouble(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, BoundBinaryExpression *binaryExpression);

llvm::Value *getResultFromBinaryOperationOnInt(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, BoundBinaryExpression *binaryExpression,
    llvm::LLVMContext *TheContext);

llvm::Value *getResultFromBinaryOperationOnBool(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, BoundBinaryExpression *binaryExpression,
    llvm::LLVMContext *TheContext);
llvm::Value *getResultFromBinaryOperationOnString(
    llvm::Value *lhsValue, llvm::Value *rhsValue, llvm::IRBuilder<> *Builder,
    llvm::Module *TheModule, llvm::LLVMContext *TheContext,
    BoundBinaryExpression *binaryExpression);
llvm::Value *getBreakCount(llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                           llvm::LLVMContext *TheContext);
llvm::Value *isBreakCountZero(llvm::Module *TheModule,
                              llvm::IRBuilder<> *Builder,
                              llvm::LLVMContext *TheContext);
llvm::Value *getGlobalZero(llvm::Module *TheModule, llvm::IRBuilder<> *Builders,
                           llvm::LLVMContext *TheContext);
void incrementBreakCount(llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                         llvm::LLVMContext *TheContext);
void decrementBrekCountIfNotZero(llvm::Module *TheModule,
                                 llvm::IRBuilder<> *Builder,
                                 llvm::LLVMContext *TheContext);

// Continue Keyword
llvm::Value *getContinueCount(llvm::Module *TheModule,
                              llvm::IRBuilder<> *Builder,
                              llvm::LLVMContext *TheContext);
llvm::Value *isContinueCountZero(llvm::Module *TheModule,
                                 llvm::IRBuilder<> *Builder,
                                 llvm::LLVMContext *TheContext);
void incrementContinueCount(llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                            llvm::LLVMContext *TheContext);
void decrementContinueCountIfNotZero(llvm::Module *TheModule,
                                     llvm::IRBuilder<> *Builder,
                                     llvm::LLVMContext *TheContext);
// SET VALUES
llvm::ConstantInt *getConstantIntFromValue(llvm::Value *value);
void setNamedValue(
    const std::string &name, llvm::Value *value,
    std::stack<std::map<std::string, llvm::Value *>> &NamedValuesStack);

void setNamedValueAlloca(const std::string &name, llvm::AllocaInst *value,
                         std::stack<std::map<std::string, llvm::AllocaInst *>>
                             &NamedValuesAllocaStack);

// GET

llvm::Value *getNamedValue(
    const std::string &name,
    std::stack<std::map<std::string, llvm::Value *>> NamedValuesStack);

llvm::AllocaInst *
getNamedValueAlloca(const std::string &name,
                    std::stack<std::map<std::string, llvm::AllocaInst *>>
                        NamedValuesAllocaStack);

// CHECK

bool isVariableDeclared(
    const std::string &name,
    std::stack<std::map<std::string, llvm::Value *>> NamedValuesStack);

// UPDATE

bool updateNamedValue(
    const std::string &name, llvm::Value *value,
    std::stack<std::map<std::string, llvm::Value *>> &NamedValuesStack);

bool updateNamedValueAlloca(
    const std::string &name, llvm::AllocaInst *value,
    std::stack<std::map<std::string, llvm::AllocaInst *>>
        &NamedValuesAllocaStack);

void printFunction(llvm::Value *value, llvm::Module *TheModule,
                   llvm::IRBuilder<> *Builder, llvm::LLVMContext *TheContext,
                   bool printNewline);

llvm::Value *
createStringComparison(llvm::Value *lhsValue, llvm::Value *rhsValue,
                       llvm::Module *TheModule, llvm::IRBuilder<> *Builder,
                       llvm::LLVMContext *TheContext, std::string functionName,
                       std::string operand = "");

llvm::Value *checkBitSet(llvm::Value *result, unsigned int bitPosition,
                         llvm::IRBuilder<> *Builder);

llvm::GlobalVariable *getNullValue(llvm::Module *TheModule,
                                   llvm::LLVMContext *TheContext,
                                   llvm::IRBuilder<> *Builder);

llvm::PHINode *
handleForLoopCondition(llvm::Value *stepValue, llvm::Value *value,
                       llvm::Value *upperBound, llvm::IRBuilder<> *Builder,
                       llvm::LLVMContext *TheContext, llvm::Module *TheModule

);

enum ENVIRONMENT { REPL, FILE };

} // namespace IRUtils

#endif